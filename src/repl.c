/*
 * repl.c - repl
 *
 *  Copyright(C) 2000-2001 by Shiro Kawai (shiro@acm.org)
 *
 *  Permission to use, copy, modify, ditribute this software and
 *  accompanying documentation for any purpose is hereby granted,
 *  provided that existing copyright notices are retained in all
 *  copies and that this notice is included verbatim in all
 *  distributions.
 *  This software is provided as is, without express or implied
 *  warranty.  In no circumstances the author(s) shall be liable
 *  for any damages arising out of the use of this software.
 *
 *  $Id: repl.c,v 1.5 2001-02-02 11:55:48 shiro Exp $
 */

#include "gauche.h"

void Scm_Repl(ScmPort *in, ScmPort *out)
{
    ScmObj c, v;
    
    for (;;) {
        SCM_PUSH_ERROR_HANDLER {
            SCM_PUTCSTR("gosh> ", out);
            SCM_FLUSH(out);
            v = Scm_Read(SCM_OBJ(in));
            if (SCM_EOFP(v)) break;
            Scm_Eval(v, SCM_NIL);
            SCM_FOR_EACH(c, Scm_VMGetResult(Scm_VM())) {
                Scm_Printf(out, "%S\n", SCM_CAR(c));
            }
        }
        SCM_POP_ERROR_HANDLER;
    }
}

