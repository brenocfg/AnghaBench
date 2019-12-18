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
struct s5p_jpeg_ctx {int /*<<< orphan*/  subsampling; TYPE_2__* jpeg; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {unsigned int version; } ;

/* Variables and functions */
 unsigned int SJPEG_EXYNOS3250 ; 
 unsigned int SJPEG_EXYNOS5420 ; 
 unsigned int SJPEG_EXYNOS5433 ; 
 int /*<<< orphan*/  V4L2_JPEG_CHROMA_SUBSAMPLING_411 ; 
 int /*<<< orphan*/  V4L2_JPEG_CHROMA_SUBSAMPLING_420 ; 
 int /*<<< orphan*/  V4L2_JPEG_CHROMA_SUBSAMPLING_422 ; 
 int /*<<< orphan*/  V4L2_JPEG_CHROMA_SUBSAMPLING_444 ; 
 int /*<<< orphan*/  V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY ; 

__attribute__((used)) static bool s5p_jpeg_subsampling_decode(struct s5p_jpeg_ctx *ctx,
					unsigned int subsampling)
{
	unsigned int version;

	switch (subsampling) {
	case 0x11:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_444;
		break;
	case 0x21:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_422;
		break;
	case 0x22:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_420;
		break;
	case 0x33:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
		break;
	case 0x41:
		/*
		 * 4:1:1 subsampling only supported by 3250, 5420, and 5433
		 * variants
		 */
		version = ctx->jpeg->variant->version;
		if (version != SJPEG_EXYNOS3250 &&
		    version != SJPEG_EXYNOS5420 &&
		    version != SJPEG_EXYNOS5433)
			return false;

		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_411;
		break;
	default:
		return false;
	}

	return true;
}