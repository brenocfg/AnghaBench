#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {scalar_t__ platform_data; int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  function; } ;
struct TYPE_5__ {TYPE_2__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; } ;
struct adp1653_flash {int /*<<< orphan*/  ctrls; TYPE_1__ subdev; int /*<<< orphan*/  power_lock; scalar_t__ platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_FLASH ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int adp1653_init_controls (struct adp1653_flash*) ; 
 int /*<<< orphan*/  adp1653_internal_ops ; 
 int adp1653_of_init (struct i2c_client*,struct adp1653_flash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp1653_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct adp1653_flash* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp1653_probe(struct i2c_client *client,
			 const struct i2c_device_id *devid)
{
	struct adp1653_flash *flash;
	int ret;

	flash = devm_kzalloc(&client->dev, sizeof(*flash), GFP_KERNEL);
	if (flash == NULL)
		return -ENOMEM;

	if (client->dev.of_node) {
		ret = adp1653_of_init(client, flash, client->dev.of_node);
		if (ret)
			return ret;
	} else {
		if (!client->dev.platform_data) {
			dev_err(&client->dev,
				"Neither DT not platform data provided\n");
			return -EINVAL;
		}
		flash->platform_data = client->dev.platform_data;
	}

	mutex_init(&flash->power_lock);

	v4l2_i2c_subdev_init(&flash->subdev, client, &adp1653_ops);
	flash->subdev.internal_ops = &adp1653_internal_ops;
	flash->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	ret = adp1653_init_controls(flash);
	if (ret)
		goto free_and_quit;

	ret = media_entity_pads_init(&flash->subdev.entity, 0, NULL);
	if (ret < 0)
		goto free_and_quit;

	flash->subdev.entity.function = MEDIA_ENT_F_FLASH;

	return 0;

free_and_quit:
	dev_err(&client->dev, "adp1653: failed to register device\n");
	v4l2_ctrl_handler_free(&flash->ctrls);
	return ret;
}