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
struct palmas_clock_info {TYPE_1__* clk_desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; scalar_t__ ext_control_pin; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_reg; int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_RESOURCE_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int palmas_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct palmas_clock_info* to_palmas_clks_info (struct clk_hw*) ; 

__attribute__((used)) static void palmas_clks_unprepare(struct clk_hw *hw)
{
	struct palmas_clock_info *cinfo = to_palmas_clks_info(hw);
	int ret;

	/*
	 * Clock can be disabled through external pin if it is externally
	 * controlled.
	 */
	if (cinfo->ext_control_pin)
		return;

	ret = palmas_update_bits(cinfo->palmas, PALMAS_RESOURCE_BASE,
				 cinfo->clk_desc->control_reg,
				 cinfo->clk_desc->enable_mask, 0);
	if (ret < 0)
		dev_err(cinfo->dev, "Reg 0x%02x update failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
}