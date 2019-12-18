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
struct mcp3911 {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 128 
 int /*<<< orphan*/  MCP3911_OFFCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCP3911_REG_STATUSCOM ; 
 int /*<<< orphan*/  MCP3911_STATUSCOM_EN_OFFCAL ; 
 struct mcp3911* iio_priv (struct iio_dev*) ; 
 int mcp3911_update (struct mcp3911*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mcp3911_write (struct mcp3911*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp3911_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *channel, int val,
			    int val2, long mask)
{
	struct mcp3911 *adc = iio_priv(indio_dev);
	int ret = -EINVAL;

	mutex_lock(&adc->lock);
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		if (val2 != 0) {
			ret = -EINVAL;
			goto out;
		}

		/* Write offset */
		ret = mcp3911_write(adc, MCP3911_OFFCAL(channel->channel), val,
				    3);
		if (ret)
			goto out;

		/* Enable offset*/
		ret = mcp3911_update(adc, MCP3911_REG_STATUSCOM,
				MCP3911_STATUSCOM_EN_OFFCAL,
				MCP3911_STATUSCOM_EN_OFFCAL, 2);
		break;
	}

out:
	mutex_unlock(&adc->lock);
	return ret;
}