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
struct octeon_droq {int /*<<< orphan*/  lock; int /*<<< orphan*/  pkts_credit_reg; struct octeon_device* oct_dev; } ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CN23XX_SLI_DEF_BP ; 
 int /*<<< orphan*/  mmiowb () ; 
 int octeon_droq_refill (struct octeon_device*,struct octeon_droq*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void octeon_droq_check_oom(struct octeon_droq *droq)
{
	int desc_refilled;
	struct octeon_device *oct = droq->oct_dev;

	if (readl(droq->pkts_credit_reg) <= CN23XX_SLI_DEF_BP) {
		spin_lock_bh(&droq->lock);
		desc_refilled = octeon_droq_refill(oct, droq);
		if (desc_refilled) {
			/* Flush the droq descriptor data to memory to be sure
			 * that when we update the credits the data in memory
			 * is accurate.
			 */
			wmb();
			writel(desc_refilled, droq->pkts_credit_reg);
			/* make sure mmio write completes */
			mmiowb();
		}
		spin_unlock_bh(&droq->lock);
	}
}