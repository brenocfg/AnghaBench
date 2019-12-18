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
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  hw_tc; TYPE_2__ hw; } ;

/* Variables and functions */
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 
 int timespec64_to_ns (struct timespec64*) ; 

__attribute__((used)) static void ixgbe_ptp_convert_to_hwtstamp(struct ixgbe_adapter *adapter,
					  struct skb_shared_hwtstamps *hwtstamp,
					  u64 timestamp)
{
	unsigned long flags;
	struct timespec64 systime;
	u64 ns;

	memset(hwtstamp, 0, sizeof(*hwtstamp));

	switch (adapter->hw.mac.type) {
	/* X550 and later hardware supposedly represent time using a seconds
	 * and nanoseconds counter, instead of raw 64bits nanoseconds. We need
	 * to convert the timestamp into cycles before it can be fed to the
	 * cyclecounter. We need an actual cyclecounter because some revisions
	 * of hardware run at a higher frequency and thus the counter does
	 * not represent seconds/nanoseconds. Instead it can be thought of as
	 * cycles and billions of cycles.
	 */
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		/* Upper 32 bits represent billions of cycles, lower 32 bits
		 * represent cycles. However, we use timespec64_to_ns for the
		 * correct math even though the units haven't been corrected
		 * yet.
		 */
		systime.tv_sec = timestamp >> 32;
		systime.tv_nsec = timestamp & 0xFFFFFFFF;

		timestamp = timespec64_to_ns(&systime);
		break;
	default:
		break;
	}

	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	ns = timecounter_cyc2time(&adapter->hw_tc, timestamp);
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	hwtstamp->hwtstamp = ns_to_ktime(ns);
}