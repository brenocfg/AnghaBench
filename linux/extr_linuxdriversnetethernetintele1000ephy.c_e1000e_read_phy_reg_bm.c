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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {int addr; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BM_PHY_PAGE_SELECT ; 
 scalar_t__ BM_WUC_PAGE ; 
 scalar_t__ IGP01E1000_PHY_PAGE_SELECT ; 
 scalar_t__ IGP_PAGE_SHIFT ; 
 scalar_t__ MAX_PHY_MULTI_PAGE_REG ; 
 scalar_t__ MAX_PHY_REG_ADDRESS ; 
 scalar_t__ e1000_access_phy_wakeup_reg_bm (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int e1000_get_phy_addr_for_bm_page (scalar_t__,scalar_t__) ; 
 scalar_t__ e1000e_read_phy_reg_mdic (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000e_write_phy_reg_mdic (struct e1000_hw*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

s32 e1000e_read_phy_reg_bm(struct e1000_hw *hw, u32 offset, u16 *data)
{
	s32 ret_val;
	u32 page = offset >> IGP_PAGE_SHIFT;

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	/* Page 800 works differently than the rest so it has its own func */
	if (page == BM_WUC_PAGE) {
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, data,
							 true, false);
		goto release;
	}

	hw->phy.addr = e1000_get_phy_addr_for_bm_page(page, offset);

	if (offset > MAX_PHY_MULTI_PAGE_REG) {
		u32 page_shift, page_select;

		/* Page select is register 31 for phy address 1 and 22 for
		 * phy address 2 and 3. Page select is shifted only for
		 * phy address 1.
		 */
		if (hw->phy.addr == 1) {
			page_shift = IGP_PAGE_SHIFT;
			page_select = IGP01E1000_PHY_PAGE_SELECT;
		} else {
			page_shift = 0;
			page_select = BM_PHY_PAGE_SELECT;
		}

		/* Page is shifted left, PHY expects (page x 32) */
		ret_val = e1000e_write_phy_reg_mdic(hw, page_select,
						    (page << page_shift));
		if (ret_val)
			goto release;
	}

	ret_val = e1000e_read_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					   data);
release:
	hw->phy.ops.release(hw);
	return ret_val;
}