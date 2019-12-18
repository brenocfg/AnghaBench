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
struct max77620_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77620_GLBLM_MASK ; 
 int /*<<< orphan*/  MAX77620_REG_INTENLBT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77620_irq_global_mask(void *irq_drv_data)
{
	struct max77620_chip *chip = irq_drv_data;
	int ret;

	ret = regmap_update_bits(chip->rmap, MAX77620_REG_INTENLBT,
				 MAX77620_GLBLM_MASK, MAX77620_GLBLM_MASK);
	if (ret < 0)
		dev_err(chip->dev, "Failed to set GLBLM: %d\n", ret);

	return ret;
}