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
typedef  int u16 ;
struct nes_hw_tune_timer {int cq_count_old; scalar_t__ cq_direction_downward; int threshold_low; int timer_direction_upward; int timer_direction_downward; int threshold_target; int threshold_high; int timer_in_use; } ;
struct nes_device {int currcq_count; int deepcq_count; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int /*<<< orphan*/  periodic_timer_lock; struct nes_hw_tune_timer tune_timer; } ;

/* Variables and functions */
 scalar_t__ NES_NIC_CQ_DOWNWARD_TREND ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nes_nic_tune_timer(struct nes_device *nesdev)
{
	unsigned long flags;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	struct nes_hw_tune_timer *shared_timer = &nesadapter->tune_timer;
	u16 cq_count = nesdev->currcq_count;

	spin_lock_irqsave(&nesadapter->periodic_timer_lock, flags);

	if (shared_timer->cq_count_old <= cq_count)
		shared_timer->cq_direction_downward = 0;
	else
		shared_timer->cq_direction_downward++;
	shared_timer->cq_count_old = cq_count;
	if (shared_timer->cq_direction_downward > NES_NIC_CQ_DOWNWARD_TREND) {
		if (cq_count <= shared_timer->threshold_low &&
		    shared_timer->threshold_low > 4) {
			shared_timer->threshold_low = shared_timer->threshold_low/2;
			shared_timer->cq_direction_downward=0;
			nesdev->currcq_count = 0;
			spin_unlock_irqrestore(&nesadapter->periodic_timer_lock, flags);
			return;
		}
	}

	if (cq_count > 1) {
		nesdev->deepcq_count += cq_count;
		if (cq_count <= shared_timer->threshold_low) {       /* increase timer gently */
			shared_timer->timer_direction_upward++;
			shared_timer->timer_direction_downward = 0;
		} else if (cq_count <= shared_timer->threshold_target) { /* balanced */
			shared_timer->timer_direction_upward = 0;
			shared_timer->timer_direction_downward = 0;
		} else if (cq_count <= shared_timer->threshold_high) {  /* decrease timer gently */
			shared_timer->timer_direction_downward++;
			shared_timer->timer_direction_upward = 0;
		} else if (cq_count <= (shared_timer->threshold_high) * 2) {
			shared_timer->timer_in_use -= 2;
			shared_timer->timer_direction_upward = 0;
			shared_timer->timer_direction_downward++;
		} else {
			shared_timer->timer_in_use -= 4;
			shared_timer->timer_direction_upward = 0;
			shared_timer->timer_direction_downward++;
		}

		if (shared_timer->timer_direction_upward > 3 ) {  /* using history */
			shared_timer->timer_in_use += 3;
			shared_timer->timer_direction_upward = 0;
			shared_timer->timer_direction_downward = 0;
		}
		if (shared_timer->timer_direction_downward > 5) { /* using history */
			shared_timer->timer_in_use -= 4 ;
			shared_timer->timer_direction_downward = 0;
			shared_timer->timer_direction_upward = 0;
		}
	}

	/* boundary checking */
	if (shared_timer->timer_in_use > shared_timer->threshold_high)
		shared_timer->timer_in_use = shared_timer->threshold_high;
	else if (shared_timer->timer_in_use < shared_timer->threshold_low)
		shared_timer->timer_in_use = shared_timer->threshold_low;

	nesdev->currcq_count = 0;

	spin_unlock_irqrestore(&nesadapter->periodic_timer_lock, flags);
}