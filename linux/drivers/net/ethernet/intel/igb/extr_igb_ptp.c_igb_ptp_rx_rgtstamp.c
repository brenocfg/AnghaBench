#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct sk_buff {int dummy; } ;
struct igb_q_vector {struct igb_adapter* adapter; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int link_speed; int /*<<< orphan*/  last_rx_timestamp; struct e1000_hw hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  hwtstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RXSTMPH ; 
 int /*<<< orphan*/  E1000_RXSTMPL ; 
 int /*<<< orphan*/  E1000_TSYNCRXCTL ; 
 int E1000_TSYNCRXCTL_VALID ; 
 int IGB_I210_RX_LATENCY_10 ; 
 int IGB_I210_RX_LATENCY_100 ; 
 int IGB_I210_RX_LATENCY_1000 ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (struct igb_adapter*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_hwtstamps (struct sk_buff*) ; 

void igb_ptp_rx_rgtstamp(struct igb_q_vector *q_vector,
			 struct sk_buff *skb)
{
	struct igb_adapter *adapter = q_vector->adapter;
	struct e1000_hw *hw = &adapter->hw;
	u64 regval;
	int adjust = 0;

	/* If this bit is set, then the RX registers contain the time stamp. No
	 * other packet will be time stamped until we read these registers, so
	 * read the registers to make them available again. Because only one
	 * packet can be time stamped at a time, we know that the register
	 * values must belong to this one here and therefore we don't need to
	 * compare any of the additional attributes stored for it.
	 *
	 * If nothing went wrong, then it should have a shared tx_flags that we
	 * can turn into a skb_shared_hwtstamps.
	 */
	if (!(rd32(E1000_TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID))
		return;

	regval = rd32(E1000_RXSTMPL);
	regval |= (u64)rd32(E1000_RXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, skb_hwtstamps(skb), regval);

	/* adjust timestamp for the RX latency based on link speed */
	if (adapter->hw.mac.type == e1000_i210) {
		switch (adapter->link_speed) {
		case SPEED_10:
			adjust = IGB_I210_RX_LATENCY_10;
			break;
		case SPEED_100:
			adjust = IGB_I210_RX_LATENCY_100;
			break;
		case SPEED_1000:
			adjust = IGB_I210_RX_LATENCY_1000;
			break;
		}
	}
	skb_hwtstamps(skb)->hwtstamp =
		ktime_sub_ns(skb_hwtstamps(skb)->hwtstamp, adjust);

	/* Update the last_rx_timestamp timer in order to enable watchdog check
	 * for error case of latched timestamp on a dropped packet.
	 */
	adapter->last_rx_timestamp = jiffies;
}