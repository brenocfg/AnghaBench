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
struct v4l2_queryctrl {int flags; int /*<<< orphan*/  id; } ;
struct pvr2_ctrl {TYPE_2__* info; TYPE_1__* hdw; } ;
struct pvr2_ctl_info {int /*<<< orphan*/ * set_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  enc_ctl_state; } ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/ * ctrl_cx2341x_set ; 
 int /*<<< orphan*/  cx2341x_ctrl_query (int /*<<< orphan*/ *,struct v4l2_queryctrl*) ; 

__attribute__((used)) static unsigned int ctrl_cx2341x_getv4lflags(struct pvr2_ctrl *cptr)
{
	struct v4l2_queryctrl qctrl;
	struct pvr2_ctl_info *info;
	qctrl.id = cptr->info->v4l_id;
	cx2341x_ctrl_query(&cptr->hdw->enc_ctl_state,&qctrl);
	/* Strip out the const so we can adjust a function pointer.  It's
	   OK to do this here because we know this is a dynamically created
	   control, so the underlying storage for the info pointer is (a)
	   private to us, and (b) not in read-only storage.  Either we do
	   this or we significantly complicate the underlying control
	   implementation. */
	info = (struct pvr2_ctl_info *)(cptr->info);
	if (qctrl.flags & V4L2_CTRL_FLAG_READ_ONLY) {
		if (info->set_value) {
			info->set_value = NULL;
		}
	} else {
		if (!(info->set_value)) {
			info->set_value = ctrl_cx2341x_set;
		}
	}
	return qctrl.flags;
}