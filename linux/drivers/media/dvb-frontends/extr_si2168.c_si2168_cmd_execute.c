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
struct si2168_dev {int /*<<< orphan*/  i2c_mutex; } ;
struct si2168_cmd {int wlen; int* args; int rlen; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct si2168_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int si2168_cmd_execute(struct i2c_client *client, struct si2168_cmd *cmd)
{
	struct si2168_dev *dev = i2c_get_clientdata(client);
	int ret;
	unsigned long timeout;

	mutex_lock(&dev->i2c_mutex);

	if (cmd->wlen) {
		/* write cmd and args for firmware */
		ret = i2c_master_send(client, cmd->args, cmd->wlen);
		if (ret < 0) {
			goto err_mutex_unlock;
		} else if (ret != cmd->wlen) {
			ret = -EREMOTEIO;
			goto err_mutex_unlock;
		}
	}

	if (cmd->rlen) {
		/* wait cmd execution terminate */
		#define TIMEOUT 70
		timeout = jiffies + msecs_to_jiffies(TIMEOUT);
		while (!time_after(jiffies, timeout)) {
			ret = i2c_master_recv(client, cmd->args, cmd->rlen);
			if (ret < 0) {
				goto err_mutex_unlock;
			} else if (ret != cmd->rlen) {
				ret = -EREMOTEIO;
				goto err_mutex_unlock;
			}

			/* firmware ready? */
			if ((cmd->args[0] >> 7) & 0x01)
				break;
		}

		dev_dbg(&client->dev, "cmd execution took %d ms\n",
				jiffies_to_msecs(jiffies) -
				(jiffies_to_msecs(timeout) - TIMEOUT));

		/* error bit set? */
		if ((cmd->args[0] >> 6) & 0x01) {
			ret = -EREMOTEIO;
			goto err_mutex_unlock;
		}

		if (!((cmd->args[0] >> 7) & 0x01)) {
			ret = -ETIMEDOUT;
			goto err_mutex_unlock;
		}
	}

	mutex_unlock(&dev->i2c_mutex);
	return 0;
err_mutex_unlock:
	mutex_unlock(&dev->i2c_mutex);
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}