#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mt6577_auxadc_read (struct iio_dev*,struct iio_chan_spec const*) ; 

__attribute__((used)) static int mt6577_auxadc_read_raw(struct iio_dev *indio_dev,
				  struct iio_chan_spec const *chan,
				  int *val,
				  int *val2,
				  long info)
{
	switch (info) {
	case IIO_CHAN_INFO_PROCESSED:
		*val = mt6577_auxadc_read(indio_dev, chan);
		if (*val < 0) {
			dev_err(indio_dev->dev.parent,
				"failed to sample data on channel[%d]\n",
				chan->channel);
			return *val;
		}
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}