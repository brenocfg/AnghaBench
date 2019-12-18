#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct srb_iocb {int /*<<< orphan*/  (* timeout ) (TYPE_5__*) ;} ;
struct req_que {int /*<<< orphan*/ ** outstanding_cmds; } ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; } ;
struct TYPE_12__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_14__ {size_t handle; TYPE_3__ u; TYPE_2__* qpair; TYPE_1__* vha; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_13__ {int /*<<< orphan*/  timer; } ;
struct TYPE_15__ {TYPE_4__ iocb_cmd; } ;
struct TYPE_11__ {struct req_que* req; } ;
struct TYPE_10__ {struct qla_hw_data* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_5__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 TYPE_5__* sp ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 TYPE_6__ u ; 

void
qla2x00_sp_timeout(struct timer_list *t)
{
	srb_t *sp = from_timer(sp, t, u.iocb_cmd.timer);
	struct srb_iocb *iocb;
	struct req_que *req;
	unsigned long flags;
	struct qla_hw_data *ha = sp->vha->hw;

	WARN_ON_ONCE(irqs_disabled());
	spin_lock_irqsave(&ha->hardware_lock, flags);
	req = sp->qpair->req;
	req->outstanding_cmds[sp->handle] = NULL;
	iocb = &sp->u.iocb_cmd;
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	iocb->timeout(sp);
}