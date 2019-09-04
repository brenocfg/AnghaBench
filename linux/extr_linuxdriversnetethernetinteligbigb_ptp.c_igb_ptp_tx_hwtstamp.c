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
typedef  int u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int link_speed; int /*<<< orphan*/  state; struct sk_buff* ptp_tx_skb; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TXSTMPH ; 
 int /*<<< orphan*/  E1000_TXSTMPL ; 
 int IGB_I210_TX_LATENCY_10 ; 
 int IGB_I210_TX_LATENCY_100 ; 
 int IGB_I210_TX_LATENCY_1000 ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  __IGB_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (struct igb_adapter*,struct skb_shared_hwtstamps*,int) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

__attribute__((used)) static void igb_ptp_tx_hwtstamp(struct igb_adapter *adapter)
{
	struct sk_buff *skb = adapter->ptp_tx_skb;
	struct e1000_hw *hw = &adapter->hw;
	struct skb_shared_hwtstamps shhwtstamps;
	u64 regval;
	int adjust = 0;

	regval = rd32(E1000_TXSTMPL);
	regval |= (u64)rd32(E1000_TXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, &shhwtstamps, regval);
	/* adjust timestamp for the TX latency based on link speed */
	if (adapter->hw.mac.type == e1000_i210) {
		switch (adapter->link_speed) {
		case SPEED_10:
			adjust = IGB_I210_TX_LATENCY_10;
			break;
		case SPEED_100:
			adjust = IGB_I210_TX_LATENCY_100;
			break;
		case SPEED_1000:
			adjust = IGB_I210_TX_LATENCY_1000;
			break;
		}
	}

	shhwtstamps.hwtstamp =
		ktime_add_ns(shhwtstamps.hwtstamp, adjust);

	/* Clear the lock early before calling skb_tstamp_tx so that
	 * applications are not woken up before the lock bit is clear. We use
	 * a copy of the skb pointer to ensure other threads can't change it
	 * while we're notifying the stack.
	 */
	adapter->ptp_tx_skb = NULL;
	clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);

	/* Notify the stack and free the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfree_skb_any(skb);
}