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
 int /*<<< orphan*/  MAX30100_REG_MODE_CONFIG ; 
 int /*<<< orphan*/  MAX30100_REG_MODE_CONFIG_TEMP_EN ; 
 int max30100_read_temp (struct max30100_data*,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max30100_get_temp(struct max30100_data *data, int *val)
{
	int ret;

	/* start acquisition */
	ret = regmap_update_bits(data->regmap, MAX30100_REG_MODE_CONFIG,
				 MAX30100_REG_MODE_CONFIG_TEMP_EN,
				 MAX30100_REG_MODE_CONFIG_TEMP_EN);
	if (ret)
		return ret;

	msleep(35);

	return max30100_read_temp(data, val);
}