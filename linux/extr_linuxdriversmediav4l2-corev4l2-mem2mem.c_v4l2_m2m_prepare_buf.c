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
struct vb2_queue {int dummy; } ;
struct v4l2_m2m_ctx {int dummy; } ;
struct v4l2_buffer {int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vb2_queue* v4l2_m2m_get_vq (struct v4l2_m2m_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_try_schedule (struct v4l2_m2m_ctx*) ; 
 int vb2_prepare_buf (struct vb2_queue*,struct v4l2_buffer*) ; 

int v4l2_m2m_prepare_buf(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
			 struct v4l2_buffer *buf)
{
	struct vb2_queue *vq;
	int ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	ret = vb2_prepare_buf(vq, buf);
	if (!ret)
		v4l2_m2m_try_schedule(m2m_ctx);

	return ret;
}