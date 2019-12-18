#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct v4l2_ctrl_handler {int error; } ;
struct bm2835_mmal_v4l2_ctrl {int type; int /*<<< orphan*/  def; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  id; int /*<<< orphan*/  imenu; int /*<<< orphan*/  step; } ;
struct bm2835_mmal_dev {TYPE_1__** ctrls; } ;
struct TYPE_8__ {int /*<<< orphan*/  v4l2_scene; } ;
struct TYPE_7__ {void* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
#define  MMAL_CONTROL_TYPE_CLUSTER 131 
#define  MMAL_CONTROL_TYPE_INT_MENU 130 
#define  MMAL_CONTROL_TYPE_STD 129 
#define  MMAL_CONTROL_TYPE_STD_MENU 128 
 int /*<<< orphan*/  V4L2_CID_SCENE_MODE ; 
 int V4L2_CTRL_COUNT ; 
 int /*<<< orphan*/  V4L2_SCENE_MODE_NONE ; 
 int /*<<< orphan*/  bm2835_mmal_ctrl_ops ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* scene_configs ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 TYPE_1__* v4l2_ctrl_new_int_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bm2835_mmal_v4l2_ctrl* v4l2_ctrls ; 

int bm2835_mmal_init_controls(struct bm2835_mmal_dev *dev,
			      struct v4l2_ctrl_handler *hdl)
{
	int c;
	const struct bm2835_mmal_v4l2_ctrl *ctrl;

	v4l2_ctrl_handler_init(hdl, V4L2_CTRL_COUNT);

	for (c = 0; c < V4L2_CTRL_COUNT; c++) {
		ctrl = &v4l2_ctrls[c];

		switch (ctrl->type) {
		case MMAL_CONTROL_TYPE_STD:
			dev->ctrls[c] =
				v4l2_ctrl_new_std(hdl,
						  &bm2835_mmal_ctrl_ops,
						  ctrl->id, ctrl->min,
						  ctrl->max, ctrl->step,
						  ctrl->def);
			break;

		case MMAL_CONTROL_TYPE_STD_MENU:
		{
			u64 mask = ctrl->min;

			if (ctrl->id == V4L2_CID_SCENE_MODE) {
				/* Special handling to work out the mask
				 * value based on the scene_configs array
				 * at runtime. Reduces the chance of
				 * mismatches.
				 */
				int i;

				mask = BIT(V4L2_SCENE_MODE_NONE);
				for (i = 0;
				     i < ARRAY_SIZE(scene_configs);
				     i++) {
					mask |= BIT(scene_configs[i].v4l2_scene);
				}
				mask = ~mask;
			}

			dev->ctrls[c] =
				v4l2_ctrl_new_std_menu(hdl,
						       &bm2835_mmal_ctrl_ops,
						       ctrl->id, ctrl->max,
						       mask, ctrl->def);
			break;
		}

		case MMAL_CONTROL_TYPE_INT_MENU:
			dev->ctrls[c] =
				v4l2_ctrl_new_int_menu(hdl,
						       &bm2835_mmal_ctrl_ops,
						       ctrl->id, ctrl->max,
						       ctrl->def, ctrl->imenu);
			break;

		case MMAL_CONTROL_TYPE_CLUSTER:
			/* skip this entry when constructing controls */
			continue;
		}

		if (hdl->error)
			break;

		dev->ctrls[c]->priv = (void *)ctrl;
	}

	if (hdl->error) {
		pr_err("error adding control %d/%d id 0x%x\n", c,
		       V4L2_CTRL_COUNT, ctrl->id);
		return hdl->error;
	}

	for (c = 0; c < V4L2_CTRL_COUNT; c++) {
		ctrl = &v4l2_ctrls[c];

		switch (ctrl->type) {
		case MMAL_CONTROL_TYPE_CLUSTER:
			v4l2_ctrl_auto_cluster(ctrl->min,
					       &dev->ctrls[c + 1],
					       ctrl->max,
					       ctrl->def);
			break;

		case MMAL_CONTROL_TYPE_STD:
		case MMAL_CONTROL_TYPE_STD_MENU:
		case MMAL_CONTROL_TYPE_INT_MENU:
			break;
		}
	}

	return 0;
}