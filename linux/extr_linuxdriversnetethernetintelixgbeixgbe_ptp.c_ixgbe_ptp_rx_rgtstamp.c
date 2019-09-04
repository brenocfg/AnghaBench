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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ixgbe_q_vector {struct ixgbe_adapter* adapter; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXSTMPH ; 
 int /*<<< orphan*/  IXGBE_RXSTMPL ; 
 int /*<<< orphan*/  IXGBE_TSYNCRXCTL ; 
 int IXGBE_TSYNCRXCTL_VALID ; 
 int /*<<< orphan*/  ixgbe_ptp_convert_to_hwtstamp (struct ixgbe_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 

void ixgbe_ptp_rx_rgtstamp(struct ixgbe_q_vector *q_vector,
			   struct sk_buff *skb)
{
	struct ixgbe_adapter *adapter;
	struct ixgbe_hw *hw;
	u64 regval = 0;
	u32 tsyncrxctl;

	/* we cannot process timestamps on a ring without a q_vector */
	if (!q_vector || !q_vector->adapter)
		return;

	adapter = q_vector->adapter;
	hw = &adapter->hw;

	/* Read the tsyncrxctl register afterwards in order to prevent taking an
	 * I/O hit on every packet.
	 */

	tsyncrxctl = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	if (!(tsyncrxctl & IXGBE_TSYNCRXCTL_VALID))
		return;

	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_RXSTMPL);
	regval |= (u64)IXGBE_READ_REG(hw, IXGBE_RXSTMPH) << 32;

	ixgbe_ptp_convert_to_hwtstamp(adapter, skb_hwtstamps(skb), regval);
}