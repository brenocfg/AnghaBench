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
struct mcp4531_data {int /*<<< orphan*/  client; TYPE_1__* cfg; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct TYPE_2__ {int* avail; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int MCP4531_WIPER_SHIFT ; 
 int MCP4531_WRITE ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 struct mcp4531_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mcp4531_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mcp4531_data *data = iio_priv(indio_dev);
	int address = chan->channel << MCP4531_WIPER_SHIFT;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val > data->cfg->avail[2] || val < 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return i2c_smbus_write_byte_data(data->client,
					 MCP4531_WRITE | address | (val >> 8),
					 val & 0xff);
}