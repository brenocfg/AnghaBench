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
struct notifier_block {int dummy; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 128 
 struct i2c_client* i2c_verify_client (struct device*) ; 
 int /*<<< orphan*/  ts_dmi_add_props (struct i2c_client*) ; 

__attribute__((used)) static int ts_dmi_notifier_call(struct notifier_block *nb,
				       unsigned long action, void *data)
{
	struct device *dev = data;
	struct i2c_client *client;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		client = i2c_verify_client(dev);
		if (client)
			ts_dmi_add_props(client);
		break;

	default:
		break;
	}

	return 0;
}