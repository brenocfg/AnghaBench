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
struct jsa1212_data {int /*<<< orphan*/  als_rng_idx; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSA1212_ALS_RNG_0_2048 ; 
 int JSA1212_CONF_IRDR_200MA ; 
 int JSA1212_CONF_PXS_SLP_50MS ; 
 int /*<<< orphan*/  JSA1212_CONF_REG ; 
 int JSA1212_INT_ALS_PRST_4CONV ; 
 int /*<<< orphan*/  JSA1212_INT_REG ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jsa1212_chip_init(struct jsa1212_data *data)
{
	int ret;

	ret = regmap_write(data->regmap, JSA1212_CONF_REG,
				(JSA1212_CONF_PXS_SLP_50MS |
				JSA1212_CONF_IRDR_200MA));
	if (ret < 0)
		return ret;

	ret = regmap_write(data->regmap, JSA1212_INT_REG,
				JSA1212_INT_ALS_PRST_4CONV);
	if (ret < 0)
		return ret;

	data->als_rng_idx = JSA1212_ALS_RNG_0_2048;

	return 0;
}