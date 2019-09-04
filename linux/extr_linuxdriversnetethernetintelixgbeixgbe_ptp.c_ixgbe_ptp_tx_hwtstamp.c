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
typedef  int u64 ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; struct sk_buff* ptp_tx_skb; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TXSTMPH ; 
 int /*<<< orphan*/  IXGBE_TXSTMPL ; 
 int /*<<< orphan*/  __IXGBE_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_ptp_convert_to_hwtstamp (struct ixgbe_adapter*,struct skb_shared_hwtstamps*,int) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

__attribute__((used)) static void ixgbe_ptp_tx_hwtstamp(struct ixgbe_adapter *adapter)
{
	struct sk_buff *skb = adapter->ptp_tx_skb;
	struct ixgbe_hw *hw = &adapter->hw;
	struct skb_shared_hwtstamps shhwtstamps;
	u64 regval = 0;

	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_TXSTMPL);
	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_TXSTMPH) << 32;
	ixgbe_ptp_convert_to_hwtstamp(adapter, &shhwtstamps, regval);

	/* Handle cleanup of the ptp_tx_skb ourselves, and unlock the state
	 * bit prior to notifying the stack via skb_tstamp_tx(). This prevents
	 * well behaved applications from attempting to timestamp again prior
	 * to the lock bit being clear.
	 */
	adapter->ptp_tx_skb = NULL;
	clear_bit_unlock(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state);

	/* Notify the stack and then free the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfree_skb_any(skb);
}