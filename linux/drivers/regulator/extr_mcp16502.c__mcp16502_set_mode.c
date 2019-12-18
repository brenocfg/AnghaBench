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
struct regulator_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MCP16502_MODE ; 
 int MCP16502_MODE_AUTO_PFM ; 
 int MCP16502_MODE_FPWM ; 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 int mcp16502_get_reg (struct regulator_dev*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _mcp16502_set_mode(struct regulator_dev *rdev, unsigned int mode,
			      unsigned int op_mode)
{
	int val;
	int reg;

	reg = mcp16502_get_reg(rdev, op_mode);
	if (reg < 0)
		return reg;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		val = MCP16502_MODE_FPWM;
		break;
	case REGULATOR_MODE_IDLE:
		val = MCP16502_MODE_AUTO_PFM;
		break;
	default:
		return -EINVAL;
	}

	reg = regmap_update_bits(rdev->regmap, reg, MCP16502_MODE, val);
	return reg;
}