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
typedef  int u8 ;
struct rm3100_data {int scale; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ RM3100_REG_CC_X ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int rm3100_set_cycle_count(struct rm3100_data *data, int val)
{
	int ret;
	u8 i;

	for (i = 0; i < 3; i++) {
		ret = regmap_write(data->regmap, RM3100_REG_CC_X + 2 * i, val);
		if (ret < 0)
			return ret;
	}

	/*
	 * The scale of this sensor depends on the cycle count value, these
	 * three values are corresponding to the cycle count value 50, 100,
	 * 200. scale = output / gain * 10^4.
	 */
	switch (val) {
	case 50:
		data->scale = 500;
		break;
	case 100:
		data->scale = 263;
		break;
	/*
	 * case 200:
	 * This function will never be called by users' code, so here we
	 * assume that it will never get a wrong parameter.
	 */
	default:
		data->scale = 133;
	}

	return 0;
}