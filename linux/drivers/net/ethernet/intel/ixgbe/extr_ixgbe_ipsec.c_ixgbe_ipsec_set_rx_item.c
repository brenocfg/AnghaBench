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
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  enum ixgbe_ipsec_tbl_sel { ____Placeholder_ixgbe_ipsec_tbl_sel } ixgbe_ipsec_tbl_sel ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_IPSRXIDX ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXIDX_TBL_SHIFT ; 
 int IXGBE_RXTXIDX_IDX_SHIFT ; 
 int IXGBE_RXTXIDX_IPS_EN ; 
 int IXGBE_RXTXIDX_WRITE ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_ipsec_set_rx_item(struct ixgbe_hw *hw, u16 idx,
				    enum ixgbe_ipsec_tbl_sel tbl)
{
	u32 reg;

	reg = IXGBE_READ_REG(hw, IXGBE_IPSRXIDX);
	reg &= IXGBE_RXTXIDX_IPS_EN;
	reg |= tbl << IXGBE_RXIDX_TBL_SHIFT |
	       idx << IXGBE_RXTXIDX_IDX_SHIFT |
	       IXGBE_RXTXIDX_WRITE;
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, reg);
	IXGBE_WRITE_FLUSH(hw);
}