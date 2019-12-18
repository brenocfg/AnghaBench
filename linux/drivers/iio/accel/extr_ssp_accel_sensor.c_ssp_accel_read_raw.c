#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ssp_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct iio_dev {TYPE_2__ dev; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  SSP_ACCELEROMETER_SENSOR ; 
 struct ssp_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_convert_to_freq (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ssp_get_sensor_delay (struct ssp_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssp_accel_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,  int *val,
			      int *val2, long mask)
{
	u32 t;
	struct ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		t = ssp_get_sensor_delay(data, SSP_ACCELEROMETER_SENSOR);
		ssp_convert_to_freq(t, val, val2);
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		break;
	}

	return -EINVAL;
}