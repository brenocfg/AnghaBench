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
struct max30102_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30102_REG_TEMP_CONFIG ; 
 int /*<<< orphan*/  MAX30102_REG_TEMP_CONFIG_TEMP_EN ; 
 int max30102_read_temp (struct max30102_data*,int*) ; 
 int max30102_set_power (struct max30102_data*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max30102_get_temp(struct max30102_data *data, int *val, bool en)
{
	int ret;

	if (en) {
		ret = max30102_set_power(data, true);
		if (ret)
			return ret;
	}

	/* start acquisition */
	ret = regmap_update_bits(data->regmap, MAX30102_REG_TEMP_CONFIG,
				 MAX30102_REG_TEMP_CONFIG_TEMP_EN,
				 MAX30102_REG_TEMP_CONFIG_TEMP_EN);
	if (ret)
		goto out;

	msleep(35);
	ret = max30102_read_temp(data, val);

out:
	if (en)
		max30102_set_power(data, false);

	return ret;
}