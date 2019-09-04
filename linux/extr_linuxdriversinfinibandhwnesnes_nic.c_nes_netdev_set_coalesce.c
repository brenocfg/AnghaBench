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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_hw_tune_timer {scalar_t__ timer_in_use_max; scalar_t__ timer_in_use_min; scalar_t__ threshold_high; scalar_t__ threshold_target; scalar_t__ threshold_low; } ;
struct nes_device {scalar_t__ regs; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int et_rx_coalesce_usecs_irq; int et_use_adaptive_rx_coalesce; int /*<<< orphan*/  timer_int_limit; scalar_t__ et_pkt_rate_low; int /*<<< orphan*/  periodic_timer_lock; struct nes_hw_tune_timer tune_timer; } ;
struct ethtool_coalesce {int rx_coalesce_usecs_irq; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ rx_coalesce_usecs_high; scalar_t__ rx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_max_coalesced_frames_low; } ;

/* Variables and functions */
 scalar_t__ NES_PERIODIC_CONTROL ; 
 int /*<<< orphan*/  NES_TIMER_INT_LIMIT ; 
 int /*<<< orphan*/  NES_TIMER_INT_LIMIT_DYNAMIC ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nes_netdev_set_coalesce(struct net_device *netdev,
		struct ethtool_coalesce	*et_coalesce)
{
	struct nes_vnic	*nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	struct nes_hw_tune_timer *shared_timer = &nesadapter->tune_timer;
	unsigned long flags;

	spin_lock_irqsave(&nesadapter->periodic_timer_lock, flags);
	if (et_coalesce->rx_max_coalesced_frames_low) {
		shared_timer->threshold_low = et_coalesce->rx_max_coalesced_frames_low;
	}
	if (et_coalesce->rx_max_coalesced_frames_irq) {
		shared_timer->threshold_target = et_coalesce->rx_max_coalesced_frames_irq;
	}
	if (et_coalesce->rx_max_coalesced_frames_high) {
		shared_timer->threshold_high = et_coalesce->rx_max_coalesced_frames_high;
	}
	if (et_coalesce->rx_coalesce_usecs_low) {
		shared_timer->timer_in_use_min = et_coalesce->rx_coalesce_usecs_low;
	}
	if (et_coalesce->rx_coalesce_usecs_high) {
		shared_timer->timer_in_use_max = et_coalesce->rx_coalesce_usecs_high;
	}
	spin_unlock_irqrestore(&nesadapter->periodic_timer_lock, flags);

	/* using this to drive total interrupt moderation */
	nesadapter->et_rx_coalesce_usecs_irq = et_coalesce->rx_coalesce_usecs_irq;
	if (et_coalesce->use_adaptive_rx_coalesce) {
		nesadapter->et_use_adaptive_rx_coalesce	= 1;
		nesadapter->timer_int_limit = NES_TIMER_INT_LIMIT_DYNAMIC;
		nesadapter->et_rx_coalesce_usecs_irq = 0;
		if (et_coalesce->pkt_rate_low) {
			nesadapter->et_pkt_rate_low = et_coalesce->pkt_rate_low;
		}
	} else {
		nesadapter->et_use_adaptive_rx_coalesce	= 0;
		nesadapter->timer_int_limit = NES_TIMER_INT_LIMIT;
		if (nesadapter->et_rx_coalesce_usecs_irq) {
			nes_write32(nesdev->regs+NES_PERIODIC_CONTROL,
					0x80000000 | ((u32)(nesadapter->et_rx_coalesce_usecs_irq*8)));
		}
	}
	return 0;
}