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
struct mcp41010_data {int* value; TYPE_1__* cfg; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct TYPE_2__ {int kohms; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int MCP41010_WIPER_MAX ; 
 struct mcp41010_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mcp41010_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mcp41010_data *data = iio_priv(indio_dev);
	int channel = chan->channel;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*val = data->value[channel];
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = MCP41010_WIPER_MAX;
		return IIO_VAL_FRACTIONAL;
	}

	return -EINVAL;
}