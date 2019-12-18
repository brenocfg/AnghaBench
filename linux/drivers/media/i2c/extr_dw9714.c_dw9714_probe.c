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
struct dw9714_device {TYPE_1__ sd; int /*<<< orphan*/  ctrls_vcm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_LENS ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 struct dw9714_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dw9714_init_controls (struct dw9714_device*) ; 
 int /*<<< orphan*/  dw9714_int_ops ; 
 int /*<<< orphan*/  dw9714_ops ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw9714_probe(struct i2c_client *client)
{
	struct dw9714_device *dw9714_dev;
	int rval;

	dw9714_dev = devm_kzalloc(&client->dev, sizeof(*dw9714_dev),
				  GFP_KERNEL);
	if (dw9714_dev == NULL)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&dw9714_dev->sd, client, &dw9714_ops);
	dw9714_dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dw9714_dev->sd.internal_ops = &dw9714_int_ops;

	rval = dw9714_init_controls(dw9714_dev);
	if (rval)
		goto err_cleanup;

	rval = media_entity_pads_init(&dw9714_dev->sd.entity, 0, NULL);
	if (rval < 0)
		goto err_cleanup;

	dw9714_dev->sd.entity.function = MEDIA_ENT_F_LENS;

	rval = v4l2_async_register_subdev(&dw9714_dev->sd);
	if (rval < 0)
		goto err_cleanup;

	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

err_cleanup:
	v4l2_ctrl_handler_free(&dw9714_dev->ctrls_vcm);
	media_entity_cleanup(&dw9714_dev->sd.entity);

	return rval;
}