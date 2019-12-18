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
struct vb2_queue {struct fimc_ctx* drv_priv; } ;
struct fimc_frame {unsigned long f_width; unsigned long f_height; unsigned int* payload; struct fimc_fmt* fmt; } ;
struct fimc_fmt {unsigned int memplanes; unsigned long* depth; int /*<<< orphan*/  color; } ;
struct fimc_ctx {struct fimc_frame d_frame; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ fimc_fmt_is_user_defined (int /*<<< orphan*/ ) ; 
 unsigned int max_t (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct fimc_ctx *ctx = vq->drv_priv;
	struct fimc_frame *frame = &ctx->d_frame;
	struct fimc_fmt *fmt = frame->fmt;
	unsigned long wh = frame->f_width * frame->f_height;
	int i;

	if (fmt == NULL)
		return -EINVAL;

	if (*num_planes) {
		if (*num_planes != fmt->memplanes)
			return -EINVAL;
		for (i = 0; i < *num_planes; i++)
			if (sizes[i] < (wh * fmt->depth[i]) / 8)
				return -EINVAL;
		return 0;
	}

	*num_planes = fmt->memplanes;

	for (i = 0; i < fmt->memplanes; i++) {
		unsigned int size = (wh * fmt->depth[i]) / 8;

		if (fimc_fmt_is_user_defined(fmt->color))
			sizes[i] = frame->payload[i];
		else
			sizes[i] = max_t(u32, size, frame->payload[i]);
	}

	return 0;
}