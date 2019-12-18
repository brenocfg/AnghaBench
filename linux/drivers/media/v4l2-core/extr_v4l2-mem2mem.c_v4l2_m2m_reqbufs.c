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
struct vb2_queue {int /*<<< orphan*/ * owner; } ;
struct v4l2_requestbuffers {scalar_t__ count; int /*<<< orphan*/  type; } ;
struct v4l2_m2m_ctx {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 struct vb2_queue* v4l2_m2m_get_vq (struct v4l2_m2m_ctx*,int /*<<< orphan*/ ) ; 
 int vb2_reqbufs (struct vb2_queue*,struct v4l2_requestbuffers*) ; 

int v4l2_m2m_reqbufs(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
		     struct v4l2_requestbuffers *reqbufs)
{
	struct vb2_queue *vq;
	int ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, reqbufs->type);
	ret = vb2_reqbufs(vq, reqbufs);
	/* If count == 0, then the owner has released all buffers and he
	   is no longer owner of the queue. Otherwise we have an owner. */
	if (ret == 0)
		vq->owner = reqbufs->count ? file->private_data : NULL;

	return ret;
}