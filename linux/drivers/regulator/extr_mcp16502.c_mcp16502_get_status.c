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
 unsigned int MCP16502_ENS ; 
 unsigned int MCP16502_FLT ; 
 int /*<<< orphan*/  MCP16502_STAT_BASE (int /*<<< orphan*/ ) ; 
 int REGULATOR_STATUS_ERROR ; 
 int REGULATOR_STATUS_OFF ; 
 int REGULATOR_STATUS_ON ; 
 int REGULATOR_STATUS_UNDEFINED ; 
 int /*<<< orphan*/  rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mcp16502_get_status(struct regulator_dev *rdev)
{
	int ret;
	unsigned int val;

	ret = regmap_read(rdev->regmap, MCP16502_STAT_BASE(rdev_get_id(rdev)),
			  &val);
	if (ret)
		return ret;

	if (val & MCP16502_FLT)
		return REGULATOR_STATUS_ERROR;
	else if (val & MCP16502_ENS)
		return REGULATOR_STATUS_ON;
	else if (!(val & MCP16502_ENS))
		return REGULATOR_STATUS_OFF;

	return REGULATOR_STATUS_UNDEFINED;
}