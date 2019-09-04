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
struct subch_data_s {int /*<<< orphan*/  sd_rlock; int /*<<< orphan*/  sd_wlock; int /*<<< orphan*/  sd_wq; int /*<<< orphan*/  sd_subch; int /*<<< orphan*/  sd_nasid; int /*<<< orphan*/  sd_rq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SAL_IROUTER_INTR_RECV ; 
 int SAL_IROUTER_INTR_XMIT ; 
 int ia64_sn_irtr_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_sn_irtr_intr_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
scdrv_interrupt(int irq, void *subch_data)
{
	struct subch_data_s *sd = subch_data;
	unsigned long flags;
	int status;

	spin_lock_irqsave(&sd->sd_rlock, flags);
	spin_lock(&sd->sd_wlock);
	status = ia64_sn_irtr_intr(sd->sd_nasid, sd->sd_subch);

	if (status > 0) {
		if (status & SAL_IROUTER_INTR_RECV) {
			wake_up(&sd->sd_rq);
		}
		if (status & SAL_IROUTER_INTR_XMIT) {
			ia64_sn_irtr_intr_disable
			    (sd->sd_nasid, sd->sd_subch,
			     SAL_IROUTER_INTR_XMIT);
			wake_up(&sd->sd_wq);
		}
	}
	spin_unlock(&sd->sd_wlock);
	spin_unlock_irqrestore(&sd->sd_rlock, flags);
	return IRQ_HANDLED;
}