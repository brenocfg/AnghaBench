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
struct mb1232_data {scalar_t__ irqnr; int /*<<< orphan*/  lock; int /*<<< orphan*/  ranging; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  MB1232_RANGE_COMMAND ; 
 int __be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static s16 mb1232_read_distance(struct mb1232_data *data)
{
	struct i2c_client *client = data->client;
	int ret;
	s16 distance;
	__be16 buf;

	mutex_lock(&data->lock);

	reinit_completion(&data->ranging);

	ret = i2c_smbus_write_byte(client, MB1232_RANGE_COMMAND);
	if (ret < 0) {
		dev_err(&client->dev, "write command - err: %d\n", ret);
		goto error_unlock;
	}

	if (data->irqnr >= 0) {
		/* it cannot take more than 100 ms */
		ret = wait_for_completion_killable_timeout(&data->ranging,
									HZ/10);
		if (ret < 0)
			goto error_unlock;
		else if (ret == 0) {
			ret = -ETIMEDOUT;
			goto error_unlock;
		}
	} else {
		/* use simple sleep if announce irq is not connected */
		msleep(15);
	}

	ret = i2c_master_recv(client, (char *)&buf, sizeof(buf));
	if (ret < 0) {
		dev_err(&client->dev, "i2c_master_recv: ret=%d\n", ret);
		goto error_unlock;
	}

	distance = __be16_to_cpu(buf);
	/* check for not returning misleading error codes */
	if (distance < 0) {
		dev_err(&client->dev, "distance=%d\n", distance);
		ret = -EINVAL;
		goto error_unlock;
	}

	mutex_unlock(&data->lock);

	return distance;

error_unlock:
	mutex_unlock(&data->lock);

	return ret;
}