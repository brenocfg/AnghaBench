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
struct mcp4131_data {int* buf; TYPE_1__* cfg; int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct TYPE_2__ {int kohms; int max_pos; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MCP4131_CMDERR (int*) ; 
 int MCP4131_RAW (int*) ; 
 int MCP4131_READ ; 
 int MCP4131_WIPER_SHIFT ; 
 struct mcp4131_data* iio_priv (struct iio_dev*) ; 
 int mcp4131_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp4131_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	int err;
	struct mcp4131_data *data = iio_priv(indio_dev);
	int address = chan->channel;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);

		data->buf[0] = (address << MCP4131_WIPER_SHIFT) | MCP4131_READ;
		data->buf[1] = 0;

		err = mcp4131_read(data->spi, data->buf, 2);
		if (err) {
			mutex_unlock(&data->lock);
			return err;
		}

		/* Error, bad address/command combination */
		if (!MCP4131_CMDERR(data->buf)) {
			mutex_unlock(&data->lock);
			return -EIO;
		}

		*val = MCP4131_RAW(data->buf);
		mutex_unlock(&data->lock);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->max_pos;
		return IIO_VAL_FRACTIONAL;
	}

	return -EINVAL;
}