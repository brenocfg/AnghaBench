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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct hp206c_data {struct i2c_client* client; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HP206C_DEV_RDY_WAIT_US ; 
 int HP206C_FLAG_DEV_RDY ; 
 int HP206C_MAX_DEV_RDY_WAIT_COUNT ; 
 int /*<<< orphan*/  HP206C_REG_INT_SRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hp206c_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct hp206c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hp206c_wait_dev_rdy(struct iio_dev *indio_dev)
{
	int ret;
	int count = 0;
	struct hp206c_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;

	while (++count <= HP206C_MAX_DEV_RDY_WAIT_COUNT) {
		ret = hp206c_read_reg(client, HP206C_REG_INT_SRC);
		if (ret < 0) {
			dev_err(&indio_dev->dev, "Failed READ_REG INT_SRC: %d\n", ret);
			return ret;
		}
		if (ret & HP206C_FLAG_DEV_RDY)
			return 0;
		usleep_range(HP206C_DEV_RDY_WAIT_US, HP206C_DEV_RDY_WAIT_US * 3 / 2);
	}
	return -ETIMEDOUT;
}