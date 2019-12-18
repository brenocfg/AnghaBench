#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath6kl_device {TYPE_2__* htc_cnxt; } ;
struct ath6kl {TYPE_1__* htc_target; } ;
struct TYPE_4__ {scalar_t__ chk_irq_status_cnt; } ;
struct TYPE_3__ {struct ath6kl_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_HIF_COMMUNICATION_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int proc_pending_irqs (struct ath6kl_device*,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int ath6kl_hif_intr_bh_handler(struct ath6kl *ar)
{
	struct ath6kl_device *dev = ar->htc_target->dev;
	unsigned long timeout;
	int status = 0;
	bool done = false;

	/*
	 * Reset counter used to flag a re-scan of IRQ status registers on
	 * the target.
	 */
	dev->htc_cnxt->chk_irq_status_cnt = 0;

	/*
	 * IRQ processing is synchronous, interrupt status registers can be
	 * re-read.
	 */
	timeout = jiffies + msecs_to_jiffies(ATH6KL_HIF_COMMUNICATION_TIMEOUT);
	while (time_before(jiffies, timeout) && !done) {
		status = proc_pending_irqs(dev, &done);
		if (status)
			break;
	}

	return status;
}