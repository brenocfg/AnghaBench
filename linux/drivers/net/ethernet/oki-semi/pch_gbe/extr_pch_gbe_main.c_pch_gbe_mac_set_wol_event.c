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
typedef  int u32 ;
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  WOL_ST; int /*<<< orphan*/  WOL_CTRL; int /*<<< orphan*/  INT_EN; int /*<<< orphan*/  TCPIP_ACC; int /*<<< orphan*/  WOL_ADDR_MASK; int /*<<< orphan*/  ADDR_MASK; } ;

/* Variables and functions */
 int PCH_GBE_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  PCH_GBE_WLA_BUSY ; 
 int PCH_GBE_WLC_WOL_MODE ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 struct pch_gbe_adapter* pch_gbe_hw_to_adapter (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_wait_clr_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_gbe_mac_set_wol_event(struct pch_gbe_hw *hw, u32 wu_evt)
{
	struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32 addr_mask;

	netdev_dbg(adapter->netdev, "wu_evt : 0x%08x  ADDR_MASK reg : 0x%08x\n",
		   wu_evt, ioread32(&hw->reg->ADDR_MASK));

	if (wu_evt) {
		/* Set Wake-On-Lan address mask */
		addr_mask = ioread32(&hw->reg->ADDR_MASK);
		iowrite32(addr_mask, &hw->reg->WOL_ADDR_MASK);
		/* wait busy */
		pch_gbe_wait_clr_bit(&hw->reg->WOL_ADDR_MASK, PCH_GBE_WLA_BUSY);
		iowrite32(0, &hw->reg->WOL_ST);
		iowrite32((wu_evt | PCH_GBE_WLC_WOL_MODE), &hw->reg->WOL_CTRL);
		iowrite32(0x02, &hw->reg->TCPIP_ACC);
		iowrite32(PCH_GBE_INT_ENABLE_MASK, &hw->reg->INT_EN);
	} else {
		iowrite32(0, &hw->reg->WOL_CTRL);
		iowrite32(0, &hw->reg->WOL_ST);
	}
	return;
}