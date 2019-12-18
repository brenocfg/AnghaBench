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
 unsigned int MCP16502_MODE ; 
#define  MCP16502_MODE_AUTO_PFM 129 
#define  MCP16502_MODE_FPWM 128 
 int /*<<< orphan*/  MCP16502_OPMODE_ACTIVE ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_INVALID ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int mcp16502_get_reg (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static unsigned int mcp16502_get_mode(struct regulator_dev *rdev)
{
	unsigned int val;
	int ret, reg;

	reg = mcp16502_get_reg(rdev, MCP16502_OPMODE_ACTIVE);
	if (reg < 0)
		return reg;

	ret = regmap_read(rdev->regmap, reg, &val);
	if (ret)
		return ret;

	switch (val & MCP16502_MODE) {
	case MCP16502_MODE_FPWM:
		return REGULATOR_MODE_NORMAL;
	case MCP16502_MODE_AUTO_PFM:
		return REGULATOR_MODE_IDLE;
	default:
		return REGULATOR_MODE_INVALID;
	}
}