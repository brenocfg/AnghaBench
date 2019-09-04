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
struct ltr501_data {int /*<<< orphan*/  reg_it; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LTR501_ALS_CONTR ; 
 int LTR501_CONTR_ALS_GAIN_MASK ; 
 int* int_time_mapping ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ltr501_set_it_time(struct ltr501_data *data, int it)
{
	int ret, i, index = -1, status;

	for (i = 0; i < ARRAY_SIZE(int_time_mapping); i++) {
		if (int_time_mapping[i] == it) {
			index = i;
			break;
		}
	}
	/* Make sure integ time index is valid */
	if (index < 0)
		return -EINVAL;

	ret = regmap_read(data->regmap, LTR501_ALS_CONTR, &status);
	if (ret < 0)
		return ret;

	if (status & LTR501_CONTR_ALS_GAIN_MASK) {
		/*
		 * 200 ms and 400 ms integ time can only be
		 * used in dynamic range 1
		 */
		if (index > 1)
			return -EINVAL;
	} else
		/* 50 ms integ time can only be used in dynamic range 2 */
		if (index == 1)
			return -EINVAL;

	return regmap_field_write(data->reg_it, index);
}