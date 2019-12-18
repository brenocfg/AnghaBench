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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_querymenu {int /*<<< orphan*/  value; int /*<<< orphan*/  index; int /*<<< orphan*/  id; } ;
struct v4l2_ctrl {int dummy; } ;
struct mipid02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_LINK_FREQ ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (struct v4l2_ctrl*) ; 
 int v4l2_querymenu (int /*<<< orphan*/ ,struct v4l2_querymenu*) ; 

__attribute__((used)) static u32 mipid02_get_link_freq_from_cid_link_freq(struct mipid02_dev *bridge,
						    struct v4l2_subdev *subdev)
{
	struct v4l2_querymenu qm = {.id = V4L2_CID_LINK_FREQ, };
	struct v4l2_ctrl *ctrl;
	int ret;

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_LINK_FREQ);
	if (!ctrl)
		return 0;
	qm.index = v4l2_ctrl_g_ctrl(ctrl);

	ret = v4l2_querymenu(subdev->ctrl_handler, &qm);
	if (ret)
		return 0;

	return qm.value;
}