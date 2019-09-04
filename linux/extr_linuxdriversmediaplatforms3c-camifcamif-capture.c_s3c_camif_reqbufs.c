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
struct v4l2_requestbuffers {scalar_t__ count; } ;
struct file {int dummy; } ;
struct camif_vp {void* owner; scalar_t__ reqbufs_count; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ CAMIF_REQ_BUFS_MIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ max_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,void*,void*) ; 
 int /*<<< orphan*/  u32 ; 
 int vb2_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_reqbufs(struct file *file, void *priv,
			     struct v4l2_requestbuffers *rb)
{
	struct camif_vp *vp = video_drvdata(file);
	int ret;

	pr_debug("[vp%d] rb count: %d, owner: %p, priv: %p\n",
		 vp->id, rb->count, vp->owner, priv);

	if (vp->owner && vp->owner != priv)
		return -EBUSY;

	if (rb->count)
		rb->count = max_t(u32, CAMIF_REQ_BUFS_MIN, rb->count);
	else
		vp->owner = NULL;

	ret = vb2_reqbufs(&vp->vb_queue, rb);
	if (ret < 0)
		return ret;

	if (rb->count && rb->count < CAMIF_REQ_BUFS_MIN) {
		rb->count = 0;
		vb2_reqbufs(&vp->vb_queue, rb);
		ret = -ENOMEM;
	}

	vp->reqbufs_count = rb->count;
	if (vp->owner == NULL && rb->count > 0)
		vp->owner = priv;

	return ret;
}