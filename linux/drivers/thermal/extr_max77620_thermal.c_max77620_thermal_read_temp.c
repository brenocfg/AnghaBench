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
struct max77620_therm_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 unsigned int MAX77620_IRQ_TJALRM1_MASK ; 
 unsigned int MAX77620_IRQ_TJALRM2_MASK ; 
 int MAX77620_NORMAL_OPERATING_TEMP ; 
 int /*<<< orphan*/  MAX77620_REG_STATLBT ; 
 int MAX77620_TJALARM1_TEMP ; 
 int MAX77620_TJALARM2_TEMP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77620_thermal_read_temp(void *data, int *temp)
{
	struct max77620_therm_info *mtherm = data;
	unsigned int val;
	int ret;

	ret = regmap_read(mtherm->rmap, MAX77620_REG_STATLBT, &val);
	if (ret < 0) {
		dev_err(mtherm->dev, "Failed to read STATLBT: %d\n", ret);
		return ret;
	}

	if (val & MAX77620_IRQ_TJALRM2_MASK)
		*temp = MAX77620_TJALARM2_TEMP;
	else if (val & MAX77620_IRQ_TJALRM1_MASK)
		*temp = MAX77620_TJALARM1_TEMP;
	else
		*temp = MAX77620_NORMAL_OPERATING_TEMP;

	return 0;
}