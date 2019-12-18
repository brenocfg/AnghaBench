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
struct mcp4018_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int MCP4018_WIPER_MAX ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int) ; 
 struct mcp4018_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mcp4018_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mcp4018_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val > MCP4018_WIPER_MAX || val < 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return i2c_smbus_write_byte(data->client, val);
}