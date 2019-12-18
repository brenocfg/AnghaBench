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
struct pa12203001_data {int /*<<< orphan*/  map; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  PA12203001_AFSR_MASK ; 
 int PA12203001_AFSR_SHIFT ; 
 int /*<<< orphan*/  PA12203001_REG_CFG0 ; 
 struct pa12203001_data* iio_priv (struct iio_dev*) ; 
 int* pa12203001_scales ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pa12203001_write_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan, int val,
				int val2, long mask)
{
	struct pa12203001_data *data = iio_priv(indio_dev);
	int i, ret, new_val;
	unsigned int reg_byte;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		ret = regmap_read(data->map, PA12203001_REG_CFG0, &reg_byte);
		if (val != 0 || ret < 0)
			return -EINVAL;
		for (i = 0; i < ARRAY_SIZE(pa12203001_scales); i++) {
			if (val2 == pa12203001_scales[i]) {
				new_val = i << PA12203001_AFSR_SHIFT;
				return regmap_update_bits(data->map,
							  PA12203001_REG_CFG0,
							  PA12203001_AFSR_MASK,
							  new_val);
			}
		}
		break;
	default:
		break;
	}

	return -EINVAL;
}