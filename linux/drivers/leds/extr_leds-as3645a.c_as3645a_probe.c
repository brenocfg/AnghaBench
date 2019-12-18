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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct as3645a {int /*<<< orphan*/  indicator_node; int /*<<< orphan*/  flash_node; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fled; struct i2c_client* client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int as3645a_detect (struct as3645a*) ; 
 int as3645a_led_class_setup (struct as3645a*) ; 
 int as3645a_parse_node (struct as3645a*,int /*<<< orphan*/ ) ; 
 int as3645a_setup (struct as3645a*) ; 
 int as3645a_v4l2_setup (struct as3645a*) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ *) ; 
 struct as3645a* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct as3645a*) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as3645a_probe(struct i2c_client *client)
{
	struct as3645a *flash;
	int rval;

	if (!dev_fwnode(&client->dev))
		return -ENODEV;

	flash = devm_kzalloc(&client->dev, sizeof(*flash), GFP_KERNEL);
	if (flash == NULL)
		return -ENOMEM;

	flash->client = client;

	rval = as3645a_parse_node(flash, dev_fwnode(&client->dev));
	if (rval < 0)
		return rval;

	rval = as3645a_detect(flash);
	if (rval < 0)
		goto out_put_nodes;

	mutex_init(&flash->mutex);
	i2c_set_clientdata(client, flash);

	rval = as3645a_setup(flash);
	if (rval)
		goto out_mutex_destroy;

	rval = as3645a_led_class_setup(flash);
	if (rval)
		goto out_mutex_destroy;

	rval = as3645a_v4l2_setup(flash);
	if (rval)
		goto out_led_classdev_flash_unregister;

	return 0;

out_led_classdev_flash_unregister:
	led_classdev_flash_unregister(&flash->fled);

out_mutex_destroy:
	mutex_destroy(&flash->mutex);

out_put_nodes:
	fwnode_handle_put(flash->flash_node);
	fwnode_handle_put(flash->indicator_node);

	return rval;
}