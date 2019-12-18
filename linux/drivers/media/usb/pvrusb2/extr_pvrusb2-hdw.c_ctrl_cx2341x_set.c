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
struct v4l2_ext_controls {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_controls* controls; } ;
struct v4l2_ext_control {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_control* controls; } ;
struct pvr2_hdw {int enc_unsafe_stale; int enc_stale; int /*<<< orphan*/  enc_ctl_state; int /*<<< orphan*/  state_encoder_run; } ;
struct pvr2_ctrl {TYPE_1__* info; struct pvr2_hdw* hdw; } ;
typedef  int /*<<< orphan*/  cs ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_2__ {int /*<<< orphan*/  v4l_id; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  VIDIOC_S_EXT_CTRLS ; 
 int cx2341x_ext_ctrls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_ext_controls*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctrl_cx2341x_set(struct pvr2_ctrl *cptr,int m,int v)
{
	int ret;
	struct pvr2_hdw *hdw = cptr->hdw;
	struct v4l2_ext_controls cs;
	struct v4l2_ext_control c1;
	memset(&cs,0,sizeof(cs));
	memset(&c1,0,sizeof(c1));
	cs.controls = &c1;
	cs.count = 1;
	c1.id = cptr->info->v4l_id;
	c1.value = v;
	ret = cx2341x_ext_ctrls(&hdw->enc_ctl_state,
				hdw->state_encoder_run, &cs,
				VIDIOC_S_EXT_CTRLS);
	if (ret == -EBUSY) {
		/* Oops.  cx2341x is telling us it's not safe to change
		   this control while we're capturing.  Make a note of this
		   fact so that the pipeline will be stopped the next time
		   controls are committed.  Then go on ahead and store this
		   change anyway. */
		ret = cx2341x_ext_ctrls(&hdw->enc_ctl_state,
					0, &cs,
					VIDIOC_S_EXT_CTRLS);
		if (!ret) hdw->enc_unsafe_stale = !0;
	}
	if (ret) return ret;
	hdw->enc_stale = !0;
	return 0;
}