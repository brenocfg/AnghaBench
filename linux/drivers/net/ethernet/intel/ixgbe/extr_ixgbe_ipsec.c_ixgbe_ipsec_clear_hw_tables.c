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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IXGBE_IPSEC_MAX_RX_IP_COUNT ; 
 scalar_t__ IXGBE_IPSEC_MAX_SA_COUNT ; 
 int /*<<< orphan*/  IXGBE_IPSRXIDX ; 
 int /*<<< orphan*/  IXGBE_IPSTXIDX ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_rx_ip (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_rx_sa (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_tx_sa (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_ipsec_clear_hw_tables(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 buf[4] = {0, 0, 0, 0};
	u16 idx;

	/* disable Rx and Tx SA lookup */
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, 0);
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, 0);

	/* scrub the tables - split the loops for the max of the IP table */
	for (idx = 0; idx < IXGBE_IPSEC_MAX_RX_IP_COUNT; idx++) {
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_rx_sa(hw, idx, 0, buf, 0, 0, 0);
		ixgbe_ipsec_set_rx_ip(hw, idx, (__be32 *)buf);
	}
	for (; idx < IXGBE_IPSEC_MAX_SA_COUNT; idx++) {
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_rx_sa(hw, idx, 0, buf, 0, 0, 0);
	}
}