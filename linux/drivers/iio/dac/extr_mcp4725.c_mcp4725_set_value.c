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
typedef  int u8 ;
struct mcp4725_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 struct mcp4725_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mcp4725_set_value(struct iio_dev *indio_dev, int val)
{
	struct mcp4725_data *data = iio_priv(indio_dev);
	u8 outbuf[2];
	int ret;

	if (val >= (1 << 12) || val < 0)
		return -EINVAL;

	outbuf[0] = (val >> 8) & 0xf;
	outbuf[1] = val & 0xff;

	ret = i2c_master_send(data->client, outbuf, 2);
	if (ret < 0)
		return ret;
	else if (ret != 2)
		return -EIO;
	else
		return 0;
}