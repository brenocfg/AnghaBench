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
struct rpr0521_data {int /*<<< orphan*/  regmap; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RPR0521_MODE_MEAS_TIME_MASK ; 
 int /*<<< orphan*/  RPR0521_REG_MODE_CTRL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpr0521_write_samp_freq_common(struct rpr0521_data *data,
				enum iio_chan_type chan_type,
				int val, int val2)
{
	int i;

	/*
	 * Ignore channel
	 * both pxs and als are setup only to same freq because of simplicity
	 */
	switch (val) {
	case 0:
		i = 0;
		break;

	case 2:
		if (val2 != 500000)
			return -EINVAL;

		i = 11;
		break;

	case 10:
		i = 6;
		break;

	default:
		return -EINVAL;
	}

	return regmap_update_bits(data->regmap,
		RPR0521_REG_MODE_CTRL,
		RPR0521_MODE_MEAS_TIME_MASK,
		i);
}