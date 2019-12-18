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
typedef  size_t u32 ;
struct video_device {int dummy; } ;
struct v4l2_ext_controls {size_t count; size_t error_idx; scalar_t__ which; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {size_t id; unsigned int size; } ;
struct v4l2_ctrl_ref {struct v4l2_ctrl_helper* helper; struct v4l2_ctrl* ctrl; } ;
struct v4l2_ctrl_helper {size_t next; struct v4l2_ctrl_ref* mref; struct v4l2_ctrl_ref* ref; } ;
struct v4l2_ctrl_handler {int /*<<< orphan*/  lock; } ;
struct v4l2_ctrl {int flags; int ncontrols; size_t id; unsigned int elems; unsigned int elem_size; int /*<<< orphan*/  is_string; scalar_t__ is_ptr; struct v4l2_ctrl** cluster; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOSPC ; 
 size_t V4L2_CID_PRIVATE_BASE ; 
 int V4L2_CTRL_FLAG_DISABLED ; 
 scalar_t__ V4L2_CTRL_ID2WHICH (size_t) ; 
 size_t V4L2_CTRL_ID_MASK ; 
 scalar_t__ V4L2_CTRL_WHICH_DEF_VAL ; 
 scalar_t__ V4L2_CTRL_WHICH_REQUEST_VAL ; 
 int /*<<< orphan*/  dprintk (struct video_device*,char*,...) ; 
 struct v4l2_ctrl_ref* find_ref_lock (struct v4l2_ctrl_handler*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_ext_ctrls(struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs,
			     struct v4l2_ctrl_helper *helpers,
			     struct video_device *vdev,
			     bool get)
{
	struct v4l2_ctrl_helper *h;
	bool have_clusters = false;
	u32 i;

	for (i = 0, h = helpers; i < cs->count; i++, h++) {
		struct v4l2_ext_control *c = &cs->controls[i];
		struct v4l2_ctrl_ref *ref;
		struct v4l2_ctrl *ctrl;
		u32 id = c->id & V4L2_CTRL_ID_MASK;

		cs->error_idx = i;

		if (cs->which &&
		    cs->which != V4L2_CTRL_WHICH_DEF_VAL &&
		    cs->which != V4L2_CTRL_WHICH_REQUEST_VAL &&
		    V4L2_CTRL_ID2WHICH(id) != cs->which) {
			dprintk(vdev,
				"invalid which 0x%x or control id 0x%x\n",
				cs->which, id);
			return -EINVAL;
		}

		/* Old-style private controls are not allowed for
		   extended controls */
		if (id >= V4L2_CID_PRIVATE_BASE) {
			dprintk(vdev,
				"old-style private controls not allowed\n");
			return -EINVAL;
		}
		ref = find_ref_lock(hdl, id);
		if (ref == NULL) {
			dprintk(vdev, "cannot find control id 0x%x\n", id);
			return -EINVAL;
		}
		h->ref = ref;
		ctrl = ref->ctrl;
		if (ctrl->flags & V4L2_CTRL_FLAG_DISABLED) {
			dprintk(vdev, "control id 0x%x is disabled\n", id);
			return -EINVAL;
		}

		if (ctrl->cluster[0]->ncontrols > 1)
			have_clusters = true;
		if (ctrl->cluster[0] != ctrl)
			ref = find_ref_lock(hdl, ctrl->cluster[0]->id);
		if (ctrl->is_ptr && !ctrl->is_string) {
			unsigned tot_size = ctrl->elems * ctrl->elem_size;

			if (c->size < tot_size) {
				/*
				 * In the get case the application first
				 * queries to obtain the size of the control.
				 */
				if (get) {
					c->size = tot_size;
					return -ENOSPC;
				}
				dprintk(vdev,
					"pointer control id 0x%x size too small, %d bytes but %d bytes needed\n",
					id, c->size, tot_size);
				return -EFAULT;
			}
			c->size = tot_size;
		}
		/* Store the ref to the master control of the cluster */
		h->mref = ref;
		/* Initially set next to 0, meaning that there is no other
		   control in this helper array belonging to the same
		   cluster */
		h->next = 0;
	}

	/* We are done if there were no controls that belong to a multi-
	   control cluster. */
	if (!have_clusters)
		return 0;

	/* The code below figures out in O(n) time which controls in the list
	   belong to the same cluster. */

	/* This has to be done with the handler lock taken. */
	mutex_lock(hdl->lock);

	/* First zero the helper field in the master control references */
	for (i = 0; i < cs->count; i++)
		helpers[i].mref->helper = NULL;
	for (i = 0, h = helpers; i < cs->count; i++, h++) {
		struct v4l2_ctrl_ref *mref = h->mref;

		/* If the mref->helper is set, then it points to an earlier
		   helper that belongs to the same cluster. */
		if (mref->helper) {
			/* Set the next field of mref->helper to the current
			   index: this means that that earlier helper now
			   points to the next helper in the same cluster. */
			mref->helper->next = i;
			/* mref should be set only for the first helper in the
			   cluster, clear the others. */
			h->mref = NULL;
		}
		/* Point the mref helper to the current helper struct. */
		mref->helper = h;
	}
	mutex_unlock(hdl->lock);
	return 0;
}