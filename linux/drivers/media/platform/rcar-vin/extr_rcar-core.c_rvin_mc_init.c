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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int error; } ;
struct TYPE_6__ {TYPE_2__* ctrl_handler; int /*<<< orphan*/  entity; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct rvin_dev {TYPE_2__ ctrl_handler; TYPE_1__ vdev; TYPE_5__ pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_5__*) ; 
 int /*<<< orphan*/  rvin_ctrl_ops ; 
 int rvin_group_get (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_group_put (struct rvin_dev*) ; 
 int rvin_mc_parse_of_graph (struct rvin_dev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int rvin_mc_init(struct rvin_dev *vin)
{
	int ret;

	vin->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vin->vdev.entity, 1, &vin->pad);
	if (ret)
		return ret;

	ret = rvin_group_get(vin);
	if (ret)
		return ret;

	ret = rvin_mc_parse_of_graph(vin);
	if (ret)
		rvin_group_put(vin);

	ret = v4l2_ctrl_handler_init(&vin->ctrl_handler, 1);
	if (ret < 0)
		return ret;

	v4l2_ctrl_new_std(&vin->ctrl_handler, &rvin_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	if (vin->ctrl_handler.error) {
		ret = vin->ctrl_handler.error;
		v4l2_ctrl_handler_free(&vin->ctrl_handler);
		return ret;
	}

	vin->vdev.ctrl_handler = &vin->ctrl_handler;

	return ret;
}