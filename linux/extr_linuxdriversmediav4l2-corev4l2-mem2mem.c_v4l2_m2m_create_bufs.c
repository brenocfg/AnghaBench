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
struct vb2_queue {int dummy; } ;
struct v4l2_m2m_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct v4l2_create_buffers {TYPE_1__ format; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vb2_queue* v4l2_m2m_get_vq (struct v4l2_m2m_ctx*,int /*<<< orphan*/ ) ; 
 int vb2_create_bufs (struct vb2_queue*,struct v4l2_create_buffers*) ; 

int v4l2_m2m_create_bufs(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
			 struct v4l2_create_buffers *create)
{
	struct vb2_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, create->format.type);
	return vb2_create_bufs(vq, create);
}