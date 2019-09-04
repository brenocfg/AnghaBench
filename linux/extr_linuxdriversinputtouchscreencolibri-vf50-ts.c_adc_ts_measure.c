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
struct iio_channel {int dummy; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLI_TOUCH_MAX_DELAY_US ; 
 int /*<<< orphan*/  COLI_TOUCH_MIN_DELAY_US ; 
 int COLI_TOUCH_NO_OF_AVGS ; 
 int /*<<< orphan*/  gpiod_set_value (struct gpio_desc*,int) ; 
 int iio_read_channel_raw (struct iio_channel*,int*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc_ts_measure(struct iio_channel *channel,
			  struct gpio_desc *plate_p, struct gpio_desc *plate_m)
{
	int i, value = 0, val = 0;
	int error;

	gpiod_set_value(plate_p, 1);
	gpiod_set_value(plate_m, 1);

	usleep_range(COLI_TOUCH_MIN_DELAY_US, COLI_TOUCH_MAX_DELAY_US);

	for (i = 0; i < COLI_TOUCH_NO_OF_AVGS; i++) {
		error = iio_read_channel_raw(channel, &val);
		if (error < 0) {
			value = error;
			goto error_iio_read;
		}

		value += val;
	}

	value /= COLI_TOUCH_NO_OF_AVGS;

error_iio_read:
	gpiod_set_value(plate_p, 0);
	gpiod_set_value(plate_m, 0);

	return value;
}