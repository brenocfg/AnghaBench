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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_dummy_devres {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i2c_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  devm_i2c_release_dummy ; 
 int /*<<< orphan*/  devres_add (struct device*,struct i2c_dummy_devres*) ; 
 struct i2c_dummy_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct i2c_dummy_devres*) ; 
 struct i2c_client* i2c_new_dummy_device (struct i2c_adapter*,int /*<<< orphan*/ ) ; 

struct i2c_client *devm_i2c_new_dummy_device(struct device *dev,
					     struct i2c_adapter *adapter,
					     u16 address)
{
	struct i2c_dummy_devres *dr;
	struct i2c_client *client;

	dr = devres_alloc(devm_i2c_release_dummy, sizeof(*dr), GFP_KERNEL);
	if (!dr)
		return ERR_PTR(-ENOMEM);

	client = i2c_new_dummy_device(adapter, address);
	if (IS_ERR(client)) {
		devres_free(dr);
	} else {
		dr->client = client;
		devres_add(dev, dr);
	}

	return client;
}