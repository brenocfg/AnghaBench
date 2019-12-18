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
struct apds9960_data {int als_adc_int_us; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_ATIME ; 
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int** apds9960_int_time ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds9960_set_it_time(struct apds9960_data *data, int val2)
{
	int ret = -EINVAL;
	int idx;

	for (idx = 0; idx < ARRAY_SIZE(apds9960_int_time); idx++) {
		if (apds9960_int_time[idx][0] == val2) {
			mutex_lock(&data->lock);
			ret = regmap_write(data->regmap, APDS9960_REG_ATIME,
						 apds9960_int_time[idx][1]);
			if (!ret)
				data->als_adc_int_us = val2;
			mutex_unlock(&data->lock);
			break;
		}
	}

	return ret;
}