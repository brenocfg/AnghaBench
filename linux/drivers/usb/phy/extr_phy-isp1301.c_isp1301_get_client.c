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
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 struct i2c_client* isp1301_i2c_client ; 
 int /*<<< orphan*/  match ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

struct i2c_client *isp1301_get_client(struct device_node *node)
{
	if (node) { /* reference of ISP1301 I2C node via DT */
		struct device *dev = bus_find_device(&i2c_bus_type, NULL,
						     node, match);
		if (!dev)
			return NULL;
		return to_i2c_client(dev);
	} else { /* non-DT: only one ISP1301 chip supported */
		return isp1301_i2c_client;
	}
}