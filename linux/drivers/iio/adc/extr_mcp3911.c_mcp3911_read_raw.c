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
struct mcp3911 {int /*<<< orphan*/  lock; int /*<<< orphan*/  vref; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MCP3911_CHANNEL (int /*<<< orphan*/ ) ; 
 int MCP3911_INT_VREF_UV ; 
 int /*<<< orphan*/  MCP3911_OFFCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct mcp3911* iio_priv (struct iio_dev*) ; 
 int mcp3911_read (struct mcp3911*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp3911_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *channel, int *val,
			    int *val2, long mask)
{
	struct mcp3911 *adc = iio_priv(indio_dev);
	int ret = -EINVAL;

	mutex_lock(&adc->lock);
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = mcp3911_read(adc,
				   MCP3911_CHANNEL(channel->channel), val, 3);
		if (ret)
			goto out;

		ret = IIO_VAL_INT;
		break;

	case IIO_CHAN_INFO_OFFSET:
		ret = mcp3911_read(adc,
				   MCP3911_OFFCAL(channel->channel), val, 3);
		if (ret)
			goto out;

		ret = IIO_VAL_INT;
		break;

	case IIO_CHAN_INFO_SCALE:
		if (adc->vref) {
			ret = regulator_get_voltage(adc->vref);
			if (ret < 0) {
				dev_err(indio_dev->dev.parent,
					"failed to get vref voltage: %d\n",
				       ret);
				goto out;
			}

			*val = ret / 1000;
		} else {
			*val = MCP3911_INT_VREF_UV;
		}

		*val2 = 24;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		break;
	}

out:
	mutex_unlock(&adc->lock);
	return ret;
}