#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct timer_list {int dummy; } ;
struct lpfc_vport {int work_port_events; int /*<<< orphan*/  work_port_lock; struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int WORKER_DISC_TMO ; 
 int /*<<< orphan*/  fc_disctmo ; 
 struct lpfc_vport* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 struct lpfc_vport* vport ; 

void
lpfc_disc_timeout(struct timer_list *t)
{
	struct lpfc_vport *vport = from_timer(vport, t, fc_disctmo);
	struct lpfc_hba   *phba = vport->phba;
	uint32_t tmo_posted;
	unsigned long flags = 0;

	if (unlikely(!phba))
		return;

	spin_lock_irqsave(&vport->work_port_lock, flags);
	tmo_posted = vport->work_port_events & WORKER_DISC_TMO;
	if (!tmo_posted)
		vport->work_port_events |= WORKER_DISC_TMO;
	spin_unlock_irqrestore(&vport->work_port_lock, flags);

	if (!tmo_posted)
		lpfc_worker_wake_up(phba);
	return;
}