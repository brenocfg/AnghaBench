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
typedef  int /*<<< orphan*/  u32 ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct v4l2_pix_format {unsigned int sizeimage; int /*<<< orphan*/  pixelformat; } ;
struct device {int dummy; } ;
struct cedrus_dev {int /*<<< orphan*/  capabilities; } ;
struct cedrus_ctx {struct v4l2_pix_format dst_fmt; struct v4l2_pix_format src_fmt; struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_DECODE_DST ; 
 int /*<<< orphan*/  CEDRUS_DECODE_SRC ; 
 int EINVAL ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cedrus_check_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cedrus_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int cedrus_queue_setup(struct vb2_queue *vq, unsigned int *nbufs,
			      unsigned int *nplanes, unsigned int sizes[],
			      struct device *alloc_devs[])
{
	struct cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	struct cedrus_dev *dev = ctx->dev;
	struct v4l2_pix_format *pix_fmt;
	u32 directions;

	if (V4L2_TYPE_IS_OUTPUT(vq->type)) {
		directions = CEDRUS_DECODE_SRC;
		pix_fmt = &ctx->src_fmt;
	} else {
		directions = CEDRUS_DECODE_DST;
		pix_fmt = &ctx->dst_fmt;
	}

	if (!cedrus_check_format(pix_fmt->pixelformat, directions,
				 dev->capabilities))
		return -EINVAL;

	if (*nplanes) {
		if (sizes[0] < pix_fmt->sizeimage)
			return -EINVAL;
	} else {
		sizes[0] = pix_fmt->sizeimage;
		*nplanes = 1;
	}

	return 0;
}