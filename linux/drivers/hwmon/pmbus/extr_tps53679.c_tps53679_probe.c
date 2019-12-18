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
struct pmbus_driver_info {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pmbus_driver_info* devm_kmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  tps53679_info ; 

__attribute__((used)) static int tps53679_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct pmbus_driver_info *info;

	info = devm_kmemdup(&client->dev, &tps53679_info, sizeof(*info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	return pmbus_do_probe(client, id, info);
}