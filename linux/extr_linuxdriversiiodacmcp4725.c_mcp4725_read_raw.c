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
struct mcp4725_data {int dac_value; int /*<<< orphan*/  vref_reg; int /*<<< orphan*/  vdd_reg; int /*<<< orphan*/  ref_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MCP472X_REF_VDD ; 
 struct mcp4725_data* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp4725_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct mcp4725_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*val = data->dac_value;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (data->ref_mode == MCP472X_REF_VDD)
			ret = regulator_get_voltage(data->vdd_reg);
		else
			ret = regulator_get_voltage(data->vref_reg);

		if (ret < 0)
			return ret;

		*val = ret / 1000;
		*val2 = 12;
		return IIO_VAL_FRACTIONAL_LOG2;
	}
	return -EINVAL;
}