#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mcp4725_data {int ref_mode; int powerdown_mode; int dac_value; TYPE_1__* client; scalar_t__ powerdown; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 
 struct mcp4725_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t mcp4725_store_eeprom(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct mcp4725_data *data = iio_priv(indio_dev);
	int tries = 20;
	u8 inoutbuf[3];
	bool state;
	int ret;

	ret = strtobool(buf, &state);
	if (ret < 0)
		return ret;

	if (!state)
		return 0;

	inoutbuf[0] = 0x60; /* write EEPROM */
	inoutbuf[0] |= data->ref_mode << 3;
	inoutbuf[0] |= data->powerdown ? ((data->powerdown_mode + 1) << 1) : 0;
	inoutbuf[1] = data->dac_value >> 4;
	inoutbuf[2] = (data->dac_value & 0xf) << 4;

	ret = i2c_master_send(data->client, inoutbuf, 3);
	if (ret < 0)
		return ret;
	else if (ret != 3)
		return -EIO;

	/* wait for write complete, takes up to 50ms */
	while (tries--) {
		msleep(20);
		ret = i2c_master_recv(data->client, inoutbuf, 3);
		if (ret < 0)
			return ret;
		else if (ret != 3)
			return -EIO;

		if (inoutbuf[0] & 0x80)
			break;
	}

	if (tries < 0) {
		dev_err(&data->client->dev,
			"mcp4725_store_eeprom() failed, incomplete\n");
		return -EIO;
	}

	return len;
}