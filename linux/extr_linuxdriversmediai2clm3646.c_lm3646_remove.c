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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct lm3646_flash {TYPE_1__ subdev_led; int /*<<< orphan*/  ctrls_led; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct lm3646_flash* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_1__*) ; 

__attribute__((used)) static int lm3646_remove(struct i2c_client *client)
{
	struct lm3646_flash *flash = i2c_get_clientdata(client);

	v4l2_device_unregister_subdev(&flash->subdev_led);
	v4l2_ctrl_handler_free(&flash->ctrls_led);
	media_entity_cleanup(&flash->subdev_led.entity);

	return 0;
}