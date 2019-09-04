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
struct mcu {int reg_ctrl; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_REG_CTRL ; 
 int /*<<< orphan*/  dev_attr_status ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mcu* glob_mcu ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mcu*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcu*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct mcu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mcu_gpiochip_add (struct mcu*) ; 
 scalar_t__ mcu_power_off ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/  shutdown_thread ; 
 int /*<<< orphan*/  shutdown_thread_fn ; 

__attribute__((used)) static int mcu_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mcu *mcu;
	int ret;

	mcu = kzalloc(sizeof(*mcu), GFP_KERNEL);
	if (!mcu)
		return -ENOMEM;

	mutex_init(&mcu->lock);
	mcu->client = client;
	i2c_set_clientdata(client, mcu);

	ret = i2c_smbus_read_byte_data(mcu->client, MCU_REG_CTRL);
	if (ret < 0)
		goto err;
	mcu->reg_ctrl = ret;

	ret = mcu_gpiochip_add(mcu);
	if (ret)
		goto err;

	/* XXX: this is potentially racy, but there is no lock for pm_power_off */
	if (!pm_power_off) {
		glob_mcu = mcu;
		pm_power_off = mcu_power_off;
		dev_info(&client->dev, "will provide power-off service\n");
	}

	if (device_create_file(&client->dev, &dev_attr_status))
		dev_err(&client->dev,
			"couldn't create device file for status\n");

	shutdown_thread = kthread_run(shutdown_thread_fn, NULL,
				      "mcu-i2c-shdn");

	return 0;
err:
	kfree(mcu);
	return ret;
}