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
struct as3722_regulators {int /*<<< orphan*/  dev; int /*<<< orphan*/  as3722; } ;
struct TYPE_2__ {int /*<<< orphan*/  sleep_ctrl_reg; int /*<<< orphan*/  sleep_ctrl_mask; } ;

/* Variables and functions */
 int AS3722_EXT_CONTROL_ENABLE1 ; 
 int AS3722_EXT_CONTROL_ENABLE3 ; 
 int EINVAL ; 
 TYPE_1__* as3722_reg_lookup ; 
 int as3722_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as3722_extreg_init(struct as3722_regulators *as3722_regs, int id,
		int ext_pwr_ctrl)
{
	int ret;
	unsigned int val;

	if ((ext_pwr_ctrl < AS3722_EXT_CONTROL_ENABLE1) ||
		(ext_pwr_ctrl > AS3722_EXT_CONTROL_ENABLE3))
		return -EINVAL;

	val =  ext_pwr_ctrl << (ffs(as3722_reg_lookup[id].sleep_ctrl_mask) - 1);
	ret = as3722_update_bits(as3722_regs->as3722,
			as3722_reg_lookup[id].sleep_ctrl_reg,
			as3722_reg_lookup[id].sleep_ctrl_mask, val);
	if (ret < 0)
		dev_err(as3722_regs->dev, "Reg 0x%02x update failed: %d\n",
			as3722_reg_lookup[id].sleep_ctrl_reg, ret);
	return ret;
}