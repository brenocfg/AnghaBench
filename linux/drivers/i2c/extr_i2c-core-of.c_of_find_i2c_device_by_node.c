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
struct i2c_client {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device_by_of_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 struct i2c_client* i2c_verify_client (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct i2c_client *of_find_i2c_device_by_node(struct device_node *node)
{
	struct device *dev;
	struct i2c_client *client;

	dev = bus_find_device_by_of_node(&i2c_bus_type, node);
	if (!dev)
		return NULL;

	client = i2c_verify_client(dev);
	if (!client)
		put_device(dev);

	return client;
}