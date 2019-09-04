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
typedef  scalar_t__ u8 ;
struct nes_hw_tune_timer {int /*<<< orphan*/  threshold_high; int /*<<< orphan*/  threshold_target; int /*<<< orphan*/  threshold_low; int /*<<< orphan*/  timer_in_use_max; int /*<<< orphan*/  timer_in_use_min; } ;
struct nes_device {struct nes_adapter* nesadapter; } ;
struct nes_adapter {int /*<<< orphan*/  periodic_timer_lock; struct nes_hw_tune_timer tune_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_JUMBO_NES_QL_HIGH ; 
 int /*<<< orphan*/  DEFAULT_JUMBO_NES_QL_LOW ; 
 int /*<<< orphan*/  DEFAULT_JUMBO_NES_QL_TARGET ; 
 int /*<<< orphan*/  DEFAULT_NES_QL_HIGH ; 
 int /*<<< orphan*/  DEFAULT_NES_QL_LOW ; 
 int /*<<< orphan*/  DEFAULT_NES_QL_TARGET ; 
 int /*<<< orphan*/  NES_NIC_FAST_TIMER_HIGH ; 
 int /*<<< orphan*/  NES_NIC_FAST_TIMER_LOW ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void  nes_nic_init_timer_defaults(struct nes_device *nesdev, u8 jumbomode)
{
	unsigned long flags;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	struct nes_hw_tune_timer *shared_timer = &nesadapter->tune_timer;

	spin_lock_irqsave(&nesadapter->periodic_timer_lock, flags);

	shared_timer->timer_in_use_min = NES_NIC_FAST_TIMER_LOW;
	shared_timer->timer_in_use_max = NES_NIC_FAST_TIMER_HIGH;
	if (jumbomode) {
		shared_timer->threshold_low    = DEFAULT_JUMBO_NES_QL_LOW;
		shared_timer->threshold_target = DEFAULT_JUMBO_NES_QL_TARGET;
		shared_timer->threshold_high   = DEFAULT_JUMBO_NES_QL_HIGH;
	} else {
		shared_timer->threshold_low    = DEFAULT_NES_QL_LOW;
		shared_timer->threshold_target = DEFAULT_NES_QL_TARGET;
		shared_timer->threshold_high   = DEFAULT_NES_QL_HIGH;
	}

	/* todo use netdev->mtu to set thresholds */
	spin_unlock_irqrestore(&nesadapter->periodic_timer_lock, flags);
}