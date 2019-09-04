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
struct tda10071_dev {int /*<<< orphan*/  cmd_execute_mutex; int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct tda10071_cmd {int /*<<< orphan*/  len; int /*<<< orphan*/  args; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tda10071_cmd_execute(struct tda10071_dev *dev,
	struct tda10071_cmd *cmd)
{
	struct i2c_client *client = dev->client;
	int ret, i;
	unsigned int uitmp;

	if (!dev->warm) {
		ret = -EFAULT;
		goto error;
	}

	mutex_lock(&dev->cmd_execute_mutex);

	/* write cmd and args for firmware */
	ret = regmap_bulk_write(dev->regmap, 0x00, cmd->args, cmd->len);
	if (ret)
		goto error_mutex_unlock;

	/* start cmd execution */
	ret = regmap_write(dev->regmap, 0x1f, 1);
	if (ret)
		goto error_mutex_unlock;

	/* wait cmd execution terminate */
	for (i = 1000, uitmp = 1; i && uitmp; i--) {
		ret = regmap_read(dev->regmap, 0x1f, &uitmp);
		if (ret)
			goto error_mutex_unlock;

		usleep_range(200, 5000);
	}

	mutex_unlock(&dev->cmd_execute_mutex);
	dev_dbg(&client->dev, "loop=%d\n", i);

	if (i == 0) {
		ret = -ETIMEDOUT;
		goto error;
	}

	return ret;
error_mutex_unlock:
	mutex_unlock(&dev->cmd_execute_mutex);
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}