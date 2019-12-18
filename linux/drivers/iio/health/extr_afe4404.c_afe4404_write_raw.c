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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int type; } ;
struct afe4404_data {int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CURRENT 129 
#define  IIO_INTENSITY 128 
 unsigned int* afe4404_channel_leds ; 
 unsigned int* afe4404_channel_offdacs ; 
 struct afe4404_data* iio_priv (struct iio_dev*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int afe4404_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct afe4404_data *afe = iio_priv(indio_dev);
	unsigned int led_field = afe4404_channel_leds[chan->address];
	unsigned int offdac_field = afe4404_channel_offdacs[chan->address];

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (mask) {
		case IIO_CHAN_INFO_OFFSET:
			return regmap_field_write(afe->fields[offdac_field], val);
		}
		break;
	case IIO_CURRENT:
		switch (mask) {
		case IIO_CHAN_INFO_RAW:
			return regmap_field_write(afe->fields[led_field], val);
		}
		break;
	default:
		break;
	}

	return -EINVAL;
}