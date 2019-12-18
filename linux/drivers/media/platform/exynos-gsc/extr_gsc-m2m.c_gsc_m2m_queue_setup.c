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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct gsc_frame {unsigned int* payload; TYPE_1__* fmt; } ;
struct gsc_ctx {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int num_planes; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct gsc_frame*) ; 
 int PTR_ERR (struct gsc_frame*) ; 
 struct gsc_frame* ctx_get_frame (struct gsc_ctx*,int /*<<< orphan*/ ) ; 
 struct gsc_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int gsc_m2m_queue_setup(struct vb2_queue *vq,
			unsigned int *num_buffers, unsigned int *num_planes,
			unsigned int sizes[], struct device *alloc_devs[])
{
	struct gsc_ctx *ctx = vb2_get_drv_priv(vq);
	struct gsc_frame *frame;
	int i;

	frame = ctx_get_frame(ctx, vq->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	if (!frame->fmt)
		return -EINVAL;

	*num_planes = frame->fmt->num_planes;
	for (i = 0; i < frame->fmt->num_planes; i++)
		sizes[i] = frame->payload[i];
	return 0;
}