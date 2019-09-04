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
struct atl1e_hw {int dummy; } ;

/* Variables and functions */
 int AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_VPD_CAP ; 
 int /*<<< orphan*/  REG_VPD_DATA ; 
 int VPD_CAP_VPD_ADDR_MASK ; 
 int VPD_CAP_VPD_ADDR_SHIFT ; 
 int VPD_CAP_VPD_FLAG ; 
 int /*<<< orphan*/  msleep (int) ; 

bool atl1e_read_eeprom(struct atl1e_hw *hw, u32 offset, u32 *p_value)
{
	int i;
	u32 control;

	if (offset & 3)
		return false; /* address do not align */

	AT_WRITE_REG(hw, REG_VPD_DATA, 0);
	control = (offset & VPD_CAP_VPD_ADDR_MASK) << VPD_CAP_VPD_ADDR_SHIFT;
	AT_WRITE_REG(hw, REG_VPD_CAP, control);

	for (i = 0; i < 10; i++) {
		msleep(2);
		control = AT_READ_REG(hw, REG_VPD_CAP);
		if (control & VPD_CAP_VPD_FLAG)
			break;
	}
	if (control & VPD_CAP_VPD_FLAG) {
		*p_value = AT_READ_REG(hw, REG_VPD_DATA);
		return true;
	}
	return false; /* timeout */
}