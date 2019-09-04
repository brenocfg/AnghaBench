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
struct iio_chan_spec {int dummy; } ;
struct hmc5843_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_CONFIG_REG_A ; 
 unsigned int HMC5843_MEAS_CONF_MASK ; 
 struct hmc5843_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static
int hmc5843_show_measurement_configuration(struct iio_dev *indio_dev,
					   const struct iio_chan_spec *chan)
{
	struct hmc5843_data *data = iio_priv(indio_dev);
	unsigned int val;
	int ret;

	ret = regmap_read(data->regmap, HMC5843_CONFIG_REG_A, &val);
	if (ret)
		return ret;

	return val & HMC5843_MEAS_CONF_MASK;
}