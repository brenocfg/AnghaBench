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
struct apds9960_data {int pxs_gain; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_CONFIG_2 ; 
 int /*<<< orphan*/  APDS9960_REG_CONFIG_2_GGAIN_MASK ; 
 int APDS9960_REG_CONFIG_2_GGAIN_MASK_SHIFT ; 
 int /*<<< orphan*/  APDS9960_REG_CONTROL ; 
 int /*<<< orphan*/  APDS9960_REG_CONTROL_PGAIN_MASK ; 
 int APDS9960_REG_CONTROL_PGAIN_MASK_SHIFT ; 
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* apds9960_pxs_gain_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds9960_set_pxs_gain(struct apds9960_data *data, int val)
{
	int ret = -EINVAL;
	int idx;

	for (idx = 0; idx < ARRAY_SIZE(apds9960_pxs_gain_map); idx++) {
		if (apds9960_pxs_gain_map[idx] == val) {
			/* pxs + gesture gains are mirrored */
			mutex_lock(&data->lock);
			ret = regmap_update_bits(data->regmap,
				APDS9960_REG_CONTROL,
				APDS9960_REG_CONTROL_PGAIN_MASK,
				idx << APDS9960_REG_CONTROL_PGAIN_MASK_SHIFT);
			if (ret) {
				mutex_unlock(&data->lock);
				break;
			}

			ret = regmap_update_bits(data->regmap,
				APDS9960_REG_CONFIG_2,
				APDS9960_REG_CONFIG_2_GGAIN_MASK,
				idx << APDS9960_REG_CONFIG_2_GGAIN_MASK_SHIFT);
			if (!ret)
				data->pxs_gain = idx;
			mutex_unlock(&data->lock);
			break;
		}
	}

	return ret;
}