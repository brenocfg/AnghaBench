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
struct ssp_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct iio_dev {TYPE_2__ dev; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  SSP_GYROSCOPE_SENSOR ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct ssp_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int ssp_change_delay (struct ssp_data*,int /*<<< orphan*/ ,int) ; 
 int ssp_convert_to_time (int,int) ; 

__attribute__((used)) static int ssp_gyro_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan, int val,
			      int val2, long mask)
{
	int ret;
	struct ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = ssp_convert_to_time(val, val2);
		ret = ssp_change_delay(data, SSP_GYROSCOPE_SENSOR, ret);
		if (ret < 0)
			dev_err(&indio_dev->dev, "gyro sensor enable fail\n");

		return ret;
	default:
		break;
	}

	return -EINVAL;
}