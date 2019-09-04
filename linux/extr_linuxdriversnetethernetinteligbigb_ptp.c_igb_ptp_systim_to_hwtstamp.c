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
typedef  int u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  tc; TYPE_2__ hw; } ;

/* Variables and functions */
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  ktime_set (int,int) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void igb_ptp_systim_to_hwtstamp(struct igb_adapter *adapter,
				       struct skb_shared_hwtstamps *hwtstamps,
				       u64 systim)
{
	unsigned long flags;
	u64 ns;

	switch (adapter->hw.mac.type) {
	case e1000_82576:
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
		spin_lock_irqsave(&adapter->tmreg_lock, flags);

		ns = timecounter_cyc2time(&adapter->tc, systim);

		spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

		memset(hwtstamps, 0, sizeof(*hwtstamps));
		hwtstamps->hwtstamp = ns_to_ktime(ns);
		break;
	case e1000_i210:
	case e1000_i211:
		memset(hwtstamps, 0, sizeof(*hwtstamps));
		/* Upper 32 bits contain s, lower 32 bits contain ns. */
		hwtstamps->hwtstamp = ktime_set(systim >> 32,
						systim & 0xFFFFFFFF);
		break;
	default:
		break;
	}
}