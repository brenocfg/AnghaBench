#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  (* ptp_setup_sdp ) (struct ixgbe_adapter*) ;int /*<<< orphan*/  last_overflow_check; int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  hw_cc; int /*<<< orphan*/  hw_tc; int /*<<< orphan*/  tstamp_config; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_ptp_set_timestamp_mode (struct ixgbe_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_ptp_start_cyclecounter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ixgbe_ptp_reset(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	unsigned long flags;

	/* reset the hardware timestamping mode */
	ixgbe_ptp_set_timestamp_mode(adapter, &adapter->tstamp_config);

	/* 82598 does not support PTP */
	if (hw->mac.type == ixgbe_mac_82598EB)
		return;

	ixgbe_ptp_start_cyclecounter(adapter);

	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	timecounter_init(&adapter->hw_tc, &adapter->hw_cc,
			 ktime_to_ns(ktime_get_real()));
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	adapter->last_overflow_check = jiffies;

	/* Now that the shift has been calculated and the systime
	 * registers reset, (re-)enable the Clock out feature
	 */
	if (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);
}