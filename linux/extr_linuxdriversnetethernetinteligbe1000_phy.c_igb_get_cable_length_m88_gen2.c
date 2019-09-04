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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {int id; int* pair_length; int min_cable_length; int max_cable_length; int cable_length; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
#define  I210_I_PHY_ID 132 
#define  I347AT4_E_PHY_ID 131 
 int /*<<< orphan*/  I347AT4_PAGE_SELECT ; 
 int /*<<< orphan*/  I347AT4_PCDC ; 
 int I347AT4_PCDC_CABLE_LENGTH_UNIT ; 
 int /*<<< orphan*/  I347AT4_PCDL0 ; 
 int /*<<< orphan*/  I347AT4_PCDL1 ; 
 int /*<<< orphan*/  I347AT4_PCDL2 ; 
 int /*<<< orphan*/  I347AT4_PCDL3 ; 
 int M88E1000_PSSR_CABLE_LENGTH ; 
 int M88E1000_PSSR_CABLE_LENGTH_SHIFT ; 
#define  M88E1112_E_PHY_ID 130 
 int /*<<< orphan*/  M88E1112_VCT_DSP_DISTANCE ; 
#define  M88E1512_E_PHY_ID 129 
#define  M88E1543_E_PHY_ID 128 
 void** e1000_m88_cable_length_table ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

s32 igb_get_cable_length_m88_gen2(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, phy_data2, index, default_page, is_cm;
	int len_tot = 0;
	u16 len_min;
	u16 len_max;

	switch (hw->phy.id) {
	case M88E1543_E_PHY_ID:
	case M88E1512_E_PHY_ID:
	case I347AT4_E_PHY_ID:
	case I210_I_PHY_ID:
		/* Remember the original page select and set it to 7 */
		ret_val = phy->ops.read_reg(hw, I347AT4_PAGE_SELECT,
					    &default_page);
		if (ret_val)
			goto out;

		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT, 0x07);
		if (ret_val)
			goto out;

		/* Check if the unit of cable length is meters or cm */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDC, &phy_data2);
		if (ret_val)
			goto out;

		is_cm = !(phy_data2 & I347AT4_PCDC_CABLE_LENGTH_UNIT);

		/* Get cable length from Pair 0 length Regs */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDL0, &phy_data);
		if (ret_val)
			goto out;

		phy->pair_length[0] = phy_data / (is_cm ? 100 : 1);
		len_tot = phy->pair_length[0];
		len_min = phy->pair_length[0];
		len_max = phy->pair_length[0];

		/* Get cable length from Pair 1 length Regs */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDL1, &phy_data);
		if (ret_val)
			goto out;

		phy->pair_length[1] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[1];
		len_min = min(len_min, phy->pair_length[1]);
		len_max = max(len_max, phy->pair_length[1]);

		/* Get cable length from Pair 2 length Regs */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDL2, &phy_data);
		if (ret_val)
			goto out;

		phy->pair_length[2] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[2];
		len_min = min(len_min, phy->pair_length[2]);
		len_max = max(len_max, phy->pair_length[2]);

		/* Get cable length from Pair 3 length Regs */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDL3, &phy_data);
		if (ret_val)
			goto out;

		phy->pair_length[3] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[3];
		len_min = min(len_min, phy->pair_length[3]);
		len_max = max(len_max, phy->pair_length[3]);

		/* Populate the phy structure with cable length in meters */
		phy->min_cable_length = len_min;
		phy->max_cable_length = len_max;
		phy->cable_length = len_tot / 4;

		/* Reset the page selec to its original value */
		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT,
					     default_page);
		if (ret_val)
			goto out;
		break;
	case M88E1112_E_PHY_ID:
		/* Remember the original page select and set it to 5 */
		ret_val = phy->ops.read_reg(hw, I347AT4_PAGE_SELECT,
					    &default_page);
		if (ret_val)
			goto out;

		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT, 0x05);
		if (ret_val)
			goto out;

		ret_val = phy->ops.read_reg(hw, M88E1112_VCT_DSP_DISTANCE,
					    &phy_data);
		if (ret_val)
			goto out;

		index = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
			M88E1000_PSSR_CABLE_LENGTH_SHIFT;
		if (index >= ARRAY_SIZE(e1000_m88_cable_length_table) - 1) {
			ret_val = -E1000_ERR_PHY;
			goto out;
		}

		phy->min_cable_length = e1000_m88_cable_length_table[index];
		phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

		phy->cable_length = (phy->min_cable_length +
				     phy->max_cable_length) / 2;

		/* Reset the page select to its original value */
		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT,
					     default_page);
		if (ret_val)
			goto out;

		break;
	default:
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

out:
	return ret_val;
}