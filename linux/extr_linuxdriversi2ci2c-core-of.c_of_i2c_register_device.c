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
struct i2c_board_info {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct i2c_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct device_node*) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int of_i2c_get_board_info (int /*<<< orphan*/ *,struct device_node*,struct i2c_board_info*) ; 

__attribute__((used)) static struct i2c_client *of_i2c_register_device(struct i2c_adapter *adap,
						 struct device_node *node)
{
	struct i2c_client *client;
	struct i2c_board_info info;
	int ret;

	dev_dbg(&adap->dev, "of_i2c: register %pOF\n", node);

	ret = of_i2c_get_board_info(&adap->dev, node, &info);
	if (ret)
		return ERR_PTR(ret);

	client = i2c_new_device(adap, &info);
	if (!client) {
		dev_err(&adap->dev, "of_i2c: Failure registering %pOF\n", node);
		return ERR_PTR(-EINVAL);
	}
	return client;
}