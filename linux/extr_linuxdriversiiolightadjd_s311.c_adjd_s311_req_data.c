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
struct iio_dev {int dummy; } ;
struct adjd_s311_data {TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJD_S311_CTRL ; 
 int ADJD_S311_CTRL_GSSR ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct adjd_s311_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int adjd_s311_req_data(struct iio_dev *indio_dev)
{
	struct adjd_s311_data *data = iio_priv(indio_dev);
	int tries = 10;

	int ret = i2c_smbus_write_byte_data(data->client, ADJD_S311_CTRL,
		ADJD_S311_CTRL_GSSR);
	if (ret < 0)
		return ret;

	while (tries--) {
		ret = i2c_smbus_read_byte_data(data->client, ADJD_S311_CTRL);
		if (ret < 0)
			return ret;
		if (!(ret & ADJD_S311_CTRL_GSSR))
			break;
		msleep(20);
	}

	if (tries < 0) {
		dev_err(&data->client->dev,
			"adjd_s311_req_data() failed, data not ready\n");
		return -EIO;
	}

	return 0;
}