#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {int addr; scalar_t__ type; int revision; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int BM_PHY_REG_NUM (int) ; 
 int BM_PHY_REG_PAGE (int) ; 
 int BM_WUC_PAGE ; 
 int HV_INTC_FC_PAGE_START ; 
 int IGP_PAGE_SHIFT ; 
 int MAX_PHY_MULTI_PAGE_REG ; 
 int MAX_PHY_REG_ADDRESS ; 
 scalar_t__ e1000_access_phy_debug_regs_hv (struct e1000_hw*,int,int*,int) ; 
 scalar_t__ e1000_access_phy_wakeup_reg_bm (struct e1000_hw*,int,int*,int,int) ; 
 int e1000_get_phy_addr_for_hv_page (int) ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_set_page_igp (struct e1000_hw*,int) ; 
 scalar_t__ e1000e_write_phy_reg_mdic (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  e_dbg (char*,int,int,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 __e1000_write_phy_reg_hv(struct e1000_hw *hw, u32 offset, u16 data,
				    bool locked, bool page_set)
{
	s32 ret_val;
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 reg = BM_PHY_REG_NUM(offset);
	u32 phy_addr = hw->phy.addr = e1000_get_phy_addr_for_hv_page(page);

	if (!locked) {
		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;
	}

	/* Page 800 works differently than the rest so it has its own func */
	if (page == BM_WUC_PAGE) {
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, &data,
							 false, page_set);
		goto out;
	}

	if (page > 0 && page < HV_INTC_FC_PAGE_START) {
		ret_val = e1000_access_phy_debug_regs_hv(hw, offset,
							 &data, false);
		goto out;
	}

	if (!page_set) {
		if (page == HV_INTC_FC_PAGE_START)
			page = 0;

		/* Workaround MDIO accesses being disabled after entering IEEE
		 * Power Down (when bit 11 of the PHY Control register is set)
		 */
		if ((hw->phy.type == e1000_phy_82578) &&
		    (hw->phy.revision >= 1) &&
		    (hw->phy.addr == 2) &&
		    !(MAX_PHY_REG_ADDRESS & reg) && (data & BIT(11))) {
			u16 data2 = 0x7EFF;

			ret_val = e1000_access_phy_debug_regs_hv(hw,
								 BIT(6) | 0x3,
								 &data2, false);
			if (ret_val)
				goto out;
		}

		if (reg > MAX_PHY_MULTI_PAGE_REG) {
			/* Page is shifted left, PHY expects (page x 32) */
			ret_val = e1000_set_page_igp(hw,
						     (page << IGP_PAGE_SHIFT));

			hw->phy.addr = phy_addr;

			if (ret_val)
				goto out;
		}
	}

	e_dbg("writing PHY page %d (or 0x%x shifted) reg 0x%x\n", page,
	      page << IGP_PAGE_SHIFT, reg);

	ret_val = e1000e_write_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & reg,
					    data);

out:
	if (!locked)
		hw->phy.ops.release(hw);

	return ret_val;
}