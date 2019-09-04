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
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_rx_queues; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IXGBE_PSRTYPE_IPV4HDR ; 
 int IXGBE_PSRTYPE_IPV6HDR ; 
 int IXGBE_PSRTYPE_L2HDR ; 
 int IXGBE_PSRTYPE_TCPHDR ; 
 int IXGBE_PSRTYPE_UDPHDR ; 
 int /*<<< orphan*/  IXGBE_VFPSRTYPE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbevf_setup_psrtype(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;

	/* PSRTYPE must be initialized in 82599 */
	u32 psrtype = IXGBE_PSRTYPE_TCPHDR | IXGBE_PSRTYPE_UDPHDR |
		      IXGBE_PSRTYPE_IPV4HDR | IXGBE_PSRTYPE_IPV6HDR |
		      IXGBE_PSRTYPE_L2HDR;

	if (adapter->num_rx_queues > 1)
		psrtype |= BIT(29);

	IXGBE_WRITE_REG(hw, IXGBE_VFPSRTYPE, psrtype);
}