#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  function; } ;
struct TYPE_5__ {TYPE_3__ entity; int /*<<< orphan*/ * internal_ops; int /*<<< orphan*/  flags; } ;
struct ak7375_device {TYPE_1__ sd; int /*<<< orphan*/  ctrls_vcm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_LENS ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int ak7375_init_controls (struct ak7375_device*) ; 
 int /*<<< orphan*/  ak7375_int_ops ; 
 int /*<<< orphan*/  ak7375_ops ; 
 struct ak7375_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak7375_probe(struct i2c_client *client)
{
	struct ak7375_device *ak7375_dev;
	int ret;

	ak7375_dev = devm_kzalloc(&client->dev, sizeof(*ak7375_dev),
				  GFP_KERNEL);
	if (!ak7375_dev)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&ak7375_dev->sd, client, &ak7375_ops);
	ak7375_dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ak7375_dev->sd.internal_ops = &ak7375_int_ops;
	ak7375_dev->sd.entity.function = MEDIA_ENT_F_LENS;

	ret = ak7375_init_controls(ak7375_dev);
	if (ret)
		goto err_cleanup;

	ret = media_entity_pads_init(&ak7375_dev->sd.entity, 0, NULL);
	if (ret < 0)
		goto err_cleanup;

	ret = v4l2_async_register_subdev(&ak7375_dev->sd);
	if (ret < 0)
		goto err_cleanup;

	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

err_cleanup:
	v4l2_ctrl_handler_free(&ak7375_dev->ctrls_vcm);
	media_entity_cleanup(&ak7375_dev->sd.entity);

	return ret;
}