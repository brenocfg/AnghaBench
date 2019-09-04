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
struct s5p_jpeg_ctx {int subsampling; TYPE_2__* jpeg; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
#define  SJPEG_EXYNOS3250 132 
#define  SJPEG_EXYNOS4 131 
#define  SJPEG_EXYNOS5420 130 
#define  SJPEG_EXYNOS5433 129 
#define  SJPEG_S5P 128 
 int V4L2_JPEG_CHROMA_SUBSAMPLING_411 ; 
 int V4L2_JPEG_CHROMA_SUBSAMPLING_420 ; 
 int V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int* exynos3250_decoded_subsampling ; 
 int* exynos4x12_decoded_subsampling ; 

__attribute__((used)) static int s5p_jpeg_to_user_subsampling(struct s5p_jpeg_ctx *ctx)
{
	switch (ctx->jpeg->variant->version) {
	case SJPEG_S5P:
		WARN_ON(ctx->subsampling > 3);
		if (ctx->subsampling > 2)
			return V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
		return ctx->subsampling;
	case SJPEG_EXYNOS3250:
	case SJPEG_EXYNOS5420:
		WARN_ON(ctx->subsampling > 6);
		if (ctx->subsampling > 3)
			return V4L2_JPEG_CHROMA_SUBSAMPLING_411;
		return exynos3250_decoded_subsampling[ctx->subsampling];
	case SJPEG_EXYNOS4:
		WARN_ON(ctx->subsampling > 3);
		if (ctx->subsampling > 2)
			return V4L2_JPEG_CHROMA_SUBSAMPLING_420;
		return exynos4x12_decoded_subsampling[ctx->subsampling];
	case SJPEG_EXYNOS5433:
		return ctx->subsampling; /* parsed from header */
	default:
		WARN_ON(ctx->subsampling > 3);
		return V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
	}
}