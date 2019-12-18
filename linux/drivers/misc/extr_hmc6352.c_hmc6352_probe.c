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
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_compass_gr ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hmc6352_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	int res;

	res = sysfs_create_group(&client->dev.kobj, &m_compass_gr);
	if (res) {
		dev_err(&client->dev, "device_create_file failed\n");
		return res;
	}
	dev_info(&client->dev, "%s HMC6352 compass chip found\n",
							client->name);
	return 0;
}