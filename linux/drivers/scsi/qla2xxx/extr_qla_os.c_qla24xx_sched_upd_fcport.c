#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ disc_state; int /*<<< orphan*/  reg_work; TYPE_1__* vha; int /*<<< orphan*/  next_disc_state; scalar_t__ sec_since_registration; int /*<<< orphan*/  jiffies_at_registration; int /*<<< orphan*/  d_id; } ;
typedef  TYPE_2__ fc_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_DELETED ; 
 scalar_t__ DSC_UPD_FCPORT ; 
 scalar_t__ IS_SW_RESV_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

void qla24xx_sched_upd_fcport(fc_port_t *fcport)
{
	unsigned long flags;

	if (IS_SW_RESV_ADDR(fcport->d_id))
		return;

	spin_lock_irqsave(&fcport->vha->work_lock, flags);
	if (fcport->disc_state == DSC_UPD_FCPORT) {
		spin_unlock_irqrestore(&fcport->vha->work_lock, flags);
		return;
	}
	fcport->jiffies_at_registration = jiffies;
	fcport->sec_since_registration = 0;
	fcport->next_disc_state = DSC_DELETED;
	fcport->disc_state = DSC_UPD_FCPORT;
	spin_unlock_irqrestore(&fcport->vha->work_lock, flags);

	queue_work(system_unbound_wq, &fcport->reg_work);
}