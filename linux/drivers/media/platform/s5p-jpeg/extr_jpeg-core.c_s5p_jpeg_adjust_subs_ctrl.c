#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* fmt; } ;
struct s5p_jpeg_ctx {TYPE_4__ out_q; TYPE_2__* jpeg; } ;
struct TYPE_7__ {int subsampling; int /*<<< orphan*/  fourcc; } ;
struct TYPE_6__ {TYPE_1__* variant; } ;
struct TYPE_5__ {int version; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SJPEG_EXYNOS3250 131 
#define  SJPEG_EXYNOS4 130 
#define  SJPEG_EXYNOS5420 129 
#define  SJPEG_S5P 128 
 int V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB32 ; 

__attribute__((used)) static int s5p_jpeg_adjust_subs_ctrl(struct s5p_jpeg_ctx *ctx, int *ctrl_val)
{
	switch (ctx->jpeg->variant->version) {
	case SJPEG_S5P:
		return 0;
	case SJPEG_EXYNOS3250:
	case SJPEG_EXYNOS5420:
		/*
		 * The exynos3250/compatible device can produce JPEG image only
		 * of 4:4:4 subsampling when given RGB32 source image.
		 */
		if (ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB32)
			*ctrl_val = 0;
		break;
	case SJPEG_EXYNOS4:
		/*
		 * The exynos4x12 device requires input raw image fourcc
		 * to be V4L2_PIX_FMT_GREY if gray jpeg format
		 * is to be set.
		 */
		if (ctx->out_q.fmt->fourcc != V4L2_PIX_FMT_GREY &&
		    *ctrl_val == V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY)
			return -EINVAL;
		break;
	}

	/*
	 * The exynos4x12 and exynos3250/compatible devices require resulting
	 * jpeg subsampling not to be lower than the input raw image
	 * subsampling.
	 */
	if (ctx->out_q.fmt->subsampling > *ctrl_val)
		*ctrl_val = ctx->out_q.fmt->subsampling;

	return 0;
}