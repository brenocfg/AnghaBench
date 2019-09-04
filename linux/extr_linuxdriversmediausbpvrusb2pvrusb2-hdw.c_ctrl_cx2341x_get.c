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
struct v4l2_ext_controls {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_controls* controls; } ;
struct v4l2_ext_control {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_control* controls; } ;
struct pvr2_ctrl {TYPE_2__* hdw; TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  cs ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_4__ {int /*<<< orphan*/  enc_ctl_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  v4l_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_G_EXT_CTRLS ; 
 int cx2341x_ext_ctrls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_ext_controls*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctrl_cx2341x_get(struct pvr2_ctrl *cptr,int *vp)
{
	int ret;
	struct v4l2_ext_controls cs;
	struct v4l2_ext_control c1;
	memset(&cs,0,sizeof(cs));
	memset(&c1,0,sizeof(c1));
	cs.controls = &c1;
	cs.count = 1;
	c1.id = cptr->info->v4l_id;
	ret = cx2341x_ext_ctrls(&cptr->hdw->enc_ctl_state, 0, &cs,
				VIDIOC_G_EXT_CTRLS);
	if (ret) return ret;
	*vp = c1.value;
	return 0;
}