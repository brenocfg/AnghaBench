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
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_RTTBCNRC ; 
 int IXGBE_RTTBCNRC_RF_DEC_MASK ; 
 int IXGBE_RTTBCNRC_RF_INT_MASK ; 
 int IXGBE_RTTBCNRC_RF_INT_SHIFT ; 
 int IXGBE_RTTBCNRC_RS_ENA ; 
 int /*<<< orphan*/  IXGBE_RTTDQSEL ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int ixgbe_link_mbps (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_tx_maxrate(struct net_device *netdev,
			    int queue_index, u32 maxrate)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 bcnrc_val = ixgbe_link_mbps(adapter);

	if (!maxrate)
		return 0;

	/* Calculate the rate factor values to set */
	bcnrc_val <<= IXGBE_RTTBCNRC_RF_INT_SHIFT;
	bcnrc_val /= maxrate;

	/* clear everything but the rate factor */
	bcnrc_val &= IXGBE_RTTBCNRC_RF_INT_MASK |
	IXGBE_RTTBCNRC_RF_DEC_MASK;

	/* enable the rate scheduler */
	bcnrc_val |= IXGBE_RTTBCNRC_RS_ENA;

	IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, queue_index);
	IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRC, bcnrc_val);

	return 0;
}