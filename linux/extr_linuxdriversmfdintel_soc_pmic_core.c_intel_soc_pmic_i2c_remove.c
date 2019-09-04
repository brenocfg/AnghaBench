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
struct intel_soc_pmic {int /*<<< orphan*/  irq_chip_data; int /*<<< orphan*/  irq; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_pwm_lookup ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_remove_lookup_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_gpio_table ; 
 int /*<<< orphan*/  pwm_remove_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_soc_pmic_i2c_remove(struct i2c_client *i2c)
{
	struct intel_soc_pmic *pmic = dev_get_drvdata(&i2c->dev);

	regmap_del_irq_chip(pmic->irq, pmic->irq_chip_data);

	/* Remove lookup table for Panel Control from the GPIO Chip */
	gpiod_remove_lookup_table(&panel_gpio_table);

	/* remove crc-pwm lookup table */
	pwm_remove_table(crc_pwm_lookup, ARRAY_SIZE(crc_pwm_lookup));

	mfd_remove_devices(&i2c->dev);

	return 0;
}