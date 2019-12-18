#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct TYPE_3__ {TYPE_2__ entity; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct lm3646_flash {int /*<<< orphan*/  ctrls_led; TYPE_1__ subdev_led; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3646_NAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_FLASH ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int lm3646_init_controls (struct lm3646_flash*) ; 
 int /*<<< orphan*/  lm3646_ops ; 
 int media_entity_pads_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3646_subdev_init(struct lm3646_flash *flash)
{
	struct i2c_client *client = to_i2c_client(flash->dev);
	int rval;

	v4l2_i2c_subdev_init(&flash->subdev_led, client, &lm3646_ops);
	flash->subdev_led.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(flash->subdev_led.name, LM3646_NAME,
		sizeof(flash->subdev_led.name));
	rval = lm3646_init_controls(flash);
	if (rval)
		goto err_out;
	rval = media_entity_pads_init(&flash->subdev_led.entity, 0, NULL);
	if (rval < 0)
		goto err_out;
	flash->subdev_led.entity.function = MEDIA_ENT_F_FLASH;
	return rval;

err_out:
	v4l2_ctrl_handler_free(&flash->ctrls_led);
	return rval;
}