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
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct axp20x_adc_iio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int axp20x_read_variable_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct axp20x_adc_iio* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int axp813_adc_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan, int *val)
{
	struct axp20x_adc_iio *info = iio_priv(indio_dev);

	*val = axp20x_read_variable_width(info->regmap, chan->address, 12);
	if (*val < 0)
		return *val;

	return IIO_VAL_INT;
}