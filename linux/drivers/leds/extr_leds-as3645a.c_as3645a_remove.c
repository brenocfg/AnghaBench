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
struct as3645a {int /*<<< orphan*/  indicator_node; int /*<<< orphan*/  flash_node; int /*<<< orphan*/  mutex; int /*<<< orphan*/  iled_cdev; int /*<<< orphan*/  fled; int /*<<< orphan*/  vfind; int /*<<< orphan*/  vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_MODE_EXT_TORCH ; 
 int /*<<< orphan*/  as3645a_set_control (struct as3645a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 struct as3645a* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_flash_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as3645a_remove(struct i2c_client *client)
{
	struct as3645a *flash = i2c_get_clientdata(client);

	as3645a_set_control(flash, AS_MODE_EXT_TORCH, false);

	v4l2_flash_release(flash->vf);
	v4l2_flash_release(flash->vfind);

	led_classdev_flash_unregister(&flash->fled);
	led_classdev_unregister(&flash->iled_cdev);

	mutex_destroy(&flash->mutex);

	fwnode_handle_put(flash->flash_node);
	fwnode_handle_put(flash->indicator_node);

	return 0;
}