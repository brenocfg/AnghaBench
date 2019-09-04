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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler; } ;
struct stimx274 {int /*<<< orphan*/  lock; TYPE_1__ ctrls; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  imx274_stop ; 
 int /*<<< orphan*/  imx274_write_table (struct stimx274*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct stimx274* to_imx274 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx274_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct stimx274 *imx274 = to_imx274(sd);

	/* stop stream */
	imx274_write_table(imx274, imx274_stop);

	v4l2_async_unregister_subdev(sd);
	v4l2_ctrl_handler_free(&imx274->ctrls.handler);
	media_entity_cleanup(&sd->entity);
	mutex_destroy(&imx274->lock);
	return 0;
}