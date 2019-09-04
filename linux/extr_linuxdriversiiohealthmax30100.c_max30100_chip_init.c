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
struct max30100_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30100_REG_INT_ENABLE ; 
 int MAX30100_REG_INT_ENABLE_FIFO_EN ; 
 int /*<<< orphan*/  MAX30100_REG_INT_ENABLE_MASK ; 
 int MAX30100_REG_INT_ENABLE_MASK_SHIFT ; 
 int /*<<< orphan*/  MAX30100_REG_MODE_CONFIG ; 
 int MAX30100_REG_MODE_CONFIG_MODE_HR_EN ; 
 int /*<<< orphan*/  MAX30100_REG_MODE_CONFIG_MODE_MASK ; 
 int MAX30100_REG_MODE_CONFIG_MODE_SPO2_EN ; 
 int /*<<< orphan*/  MAX30100_REG_SPO2_CONFIG ; 
 int MAX30100_REG_SPO2_CONFIG_100HZ ; 
 int MAX30100_REG_SPO2_CONFIG_HI_RES_EN ; 
 int max30100_led_init (struct max30100_data*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max30100_chip_init(struct max30100_data *data)
{
	int ret;

	/* setup LED current settings */
	ret = max30100_led_init(data);
	if (ret)
		return ret;

	/* enable hi-res SPO2 readings at 100Hz */
	ret = regmap_write(data->regmap, MAX30100_REG_SPO2_CONFIG,
				 MAX30100_REG_SPO2_CONFIG_HI_RES_EN |
				 MAX30100_REG_SPO2_CONFIG_100HZ);
	if (ret)
		return ret;

	/* enable SPO2 mode */
	ret = regmap_update_bits(data->regmap, MAX30100_REG_MODE_CONFIG,
				 MAX30100_REG_MODE_CONFIG_MODE_MASK,
				 MAX30100_REG_MODE_CONFIG_MODE_HR_EN |
				 MAX30100_REG_MODE_CONFIG_MODE_SPO2_EN);
	if (ret)
		return ret;

	/* enable FIFO interrupt */
	return regmap_update_bits(data->regmap, MAX30100_REG_INT_ENABLE,
				 MAX30100_REG_INT_ENABLE_MASK,
				 MAX30100_REG_INT_ENABLE_FIFO_EN
				 << MAX30100_REG_INT_ENABLE_MASK_SHIFT);
}