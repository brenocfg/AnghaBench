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
typedef  unsigned int u8 ;
struct max77843_muic_info {int /*<<< orphan*/  dev; struct max77693_dev* max77843; } ;
struct max77693_dev {int /*<<< orphan*/  regmap_muic; } ;

/* Variables and functions */
 unsigned int MAX77843_MUIC_CONTROL1_COM_SW ; 
 unsigned int MAX77843_MUIC_CONTROL1_NOBCCOMP_MASK ; 
 unsigned int MAX77843_MUIC_CONTROL1_SW_OPEN ; 
 unsigned int MAX77843_MUIC_CONTROL2_CPEN_MASK ; 
 unsigned int MAX77843_MUIC_CONTROL2_LOWPWR_MASK ; 
 int /*<<< orphan*/  MAX77843_MUIC_REG_CONTROL1 ; 
 int /*<<< orphan*/  MAX77843_MUIC_REG_CONTROL2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int max77843_muic_set_path(struct max77843_muic_info *info,
		u8 val, bool attached, bool nobccomp)
{
	struct max77693_dev *max77843 = info->max77843;
	int ret = 0;
	unsigned int ctrl1, ctrl2;

	if (attached)
		ctrl1 = val;
	else
		ctrl1 = MAX77843_MUIC_CONTROL1_SW_OPEN;
	if (nobccomp) {
		/* Disable BC1.2 protocol and force manual switch control */
		ctrl1 |= MAX77843_MUIC_CONTROL1_NOBCCOMP_MASK;
	}

	ret = regmap_update_bits(max77843->regmap_muic,
			MAX77843_MUIC_REG_CONTROL1,
			MAX77843_MUIC_CONTROL1_COM_SW |
				MAX77843_MUIC_CONTROL1_NOBCCOMP_MASK,
			ctrl1);
	if (ret < 0) {
		dev_err(info->dev, "Cannot switch MUIC port\n");
		return ret;
	}

	if (attached)
		ctrl2 = MAX77843_MUIC_CONTROL2_CPEN_MASK;
	else
		ctrl2 = MAX77843_MUIC_CONTROL2_LOWPWR_MASK;

	ret = regmap_update_bits(max77843->regmap_muic,
			MAX77843_MUIC_REG_CONTROL2,
			MAX77843_MUIC_CONTROL2_LOWPWR_MASK |
			MAX77843_MUIC_CONTROL2_CPEN_MASK, ctrl2);
	if (ret < 0) {
		dev_err(info->dev, "Cannot update lowpower mode\n");
		return ret;
	}

	dev_dbg(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	return 0;
}