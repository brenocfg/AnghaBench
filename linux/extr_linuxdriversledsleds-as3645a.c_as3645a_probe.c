#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct as3645a_names {int dummy; } ;
struct as3645a {int /*<<< orphan*/  indicator_node; int /*<<< orphan*/  flash_node; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fled; struct i2c_client* client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int as3645a_detect (struct as3645a*) ; 
 int as3645a_led_class_setup (struct as3645a*,struct as3645a_names*) ; 
 int as3645a_parse_node (struct as3645a*,struct as3645a_names*,int /*<<< orphan*/ *) ; 
 int as3645a_setup (struct as3645a*) ; 
 int as3645a_v4l2_setup (struct as3645a*) ; 
 struct as3645a* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct as3645a*) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as3645a_probe(struct i2c_client *client)
{
	struct as3645a_names names;
	struct as3645a *flash;
	int rval;

	if (client->dev.of_node == NULL)
		return -ENODEV;

	flash = devm_kzalloc(&client->dev, sizeof(*flash), GFP_KERNEL);
	if (flash == NULL)
		return -ENOMEM;

	flash->client = client;

	rval = as3645a_parse_node(flash, &names, client->dev.of_node);
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

	rval = as3645a_led_class_setup(flash, &names);
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
	of_node_put(flash->flash_node);
	of_node_put(flash->indicator_node);

	return rval;
}