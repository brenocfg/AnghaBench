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
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_IPSRXIDX ; 
 int /*<<< orphan*/  IXGBE_IPSTXIDX ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXTXIDX_IPS_EN ; 
 int /*<<< orphan*/  IXGBE_SECRXCTRL ; 
 int /*<<< orphan*/  IXGBE_SECTXBUFFAF ; 
 int /*<<< orphan*/  IXGBE_SECTXCTRL ; 
 int IXGBE_SECTXCTRL_STORE_FORWARD ; 
 int /*<<< orphan*/  IXGBE_SECTXMINIFG ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_ipsec_stop_data (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_ipsec_start_engine(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reg;

	ixgbe_ipsec_stop_data(adapter);

	/* Set minimum IFG between packets to 3 */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	reg = (reg & 0xfffffff0) | 0x3;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, reg);

	/* Set "tx security buffer almost full threshold" to 0x15 so that the
	 * almost full indication is generated only after buffer contains at
	 * least an entire jumbo packet.
	 */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXBUFFAF);
	reg = (reg & 0xfffffc00) | 0x15;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXBUFFAF, reg);

	/* restart the data paths by clearing the DISABLE bits */
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, 0);
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, IXGBE_SECTXCTRL_STORE_FORWARD);

	/* enable Rx and Tx SA lookup */
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, IXGBE_RXTXIDX_IPS_EN);
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, IXGBE_RXTXIDX_IPS_EN);

	IXGBE_WRITE_FLUSH(hw);
}