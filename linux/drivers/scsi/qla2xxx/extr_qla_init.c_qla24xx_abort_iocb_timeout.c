#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_9__ {int /*<<< orphan*/  comp_status; } ;
struct TYPE_10__ {TYPE_3__ abt; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; TYPE_2__* req; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* done ) (TYPE_5__*,int /*<<< orphan*/ ) ;struct qla_qpair* qpair; TYPE_1__ u; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_8__ {size_t num_outstanding_cmds; TYPE_5__** outstanding_cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_TIMEOUT ; 
 int /*<<< orphan*/  QLA_OS_TIMER_EXPIRED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla24xx_abort_iocb_timeout(void *data)
{
	srb_t *sp = data;
	struct srb_iocb *abt = &sp->u.iocb_cmd;
	struct qla_qpair *qpair = sp->qpair;
	u32 handle;
	unsigned long flags;

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	for (handle = 1; handle < qpair->req->num_outstanding_cmds; handle++) {
		/* removing the abort */
		if (qpair->req->outstanding_cmds[handle] == sp) {
			qpair->req->outstanding_cmds[handle] = NULL;
			break;
		}
	}
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	abt->u.abt.comp_status = CS_TIMEOUT;
	sp->done(sp, QLA_OS_TIMER_EXPIRED);
}