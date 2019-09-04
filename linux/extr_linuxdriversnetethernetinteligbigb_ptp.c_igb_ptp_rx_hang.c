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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct igb_adapter {unsigned long last_rx_ptp_check; unsigned long last_rx_timestamp; TYPE_1__* pdev; int /*<<< orphan*/  rx_hwtstamp_cleared; struct e1000_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RXSTMPH ; 
 int /*<<< orphan*/  E1000_TSYNCRXCTL ; 
 int E1000_TSYNCRXCTL_VALID ; 
 int HZ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ e1000_82576 ; 
 void* jiffies ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 

void igb_ptp_rx_hang(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 tsyncrxctl = rd32(E1000_TSYNCRXCTL);
	unsigned long rx_event;

	/* Other hardware uses per-packet timestamps */
	if (hw->mac.type != e1000_82576)
		return;

	/* If we don't have a valid timestamp in the registers, just update the
	 * timeout counter and exit
	 */
	if (!(tsyncrxctl & E1000_TSYNCRXCTL_VALID)) {
		adapter->last_rx_ptp_check = jiffies;
		return;
	}

	/* Determine the most recent watchdog or rx_timestamp event */
	rx_event = adapter->last_rx_ptp_check;
	if (time_after(adapter->last_rx_timestamp, rx_event))
		rx_event = adapter->last_rx_timestamp;

	/* Only need to read the high RXSTMP register to clear the lock */
	if (time_is_before_jiffies(rx_event + 5 * HZ)) {
		rd32(E1000_RXSTMPH);
		adapter->last_rx_ptp_check = jiffies;
		adapter->rx_hwtstamp_cleared++;
		dev_warn(&adapter->pdev->dev, "clearing Rx timestamp hang\n");
	}
}