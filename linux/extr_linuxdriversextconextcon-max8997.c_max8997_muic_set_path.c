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
typedef  int u8 ;
struct max8997_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  muic; } ;

/* Variables and functions */
 int COMP_SW_MASK ; 
 int CONTROL1_SW_OPEN ; 
 int CONTROL2_CPEN_MASK ; 
 int CONTROL2_LOWPWR_MASK ; 
 int /*<<< orphan*/  MAX8997_MUIC_REG_CONTROL1 ; 
 int /*<<< orphan*/  MAX8997_MUIC_REG_CONTROL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int max8997_update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max8997_muic_set_path(struct max8997_muic_info *info,
		u8 val, bool attached)
{
	int ret;
	u8 ctrl1, ctrl2 = 0;

	if (attached)
		ctrl1 = val;
	else
		ctrl1 = CONTROL1_SW_OPEN;

	ret = max8997_update_reg(info->muic,
			MAX8997_MUIC_REG_CONTROL1, ctrl1, COMP_SW_MASK);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	if (attached)
		ctrl2 |= CONTROL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	else
		ctrl2 |= CONTROL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = max8997_update_reg(info->muic,
			MAX8997_MUIC_REG_CONTROL2, ctrl2,
			CONTROL2_LOWPWR_MASK | CONTROL2_CPEN_MASK);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	dev_info(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	return 0;
}