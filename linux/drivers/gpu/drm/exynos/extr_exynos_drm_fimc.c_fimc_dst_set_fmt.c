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
typedef  int u32 ;
struct fimc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
 int DRM_FORMAT_AYUV ; 
#define  DRM_FORMAT_NV12 141 
#define  DRM_FORMAT_NV16 140 
#define  DRM_FORMAT_NV21 139 
#define  DRM_FORMAT_NV61 138 
#define  DRM_FORMAT_RGB565 137 
#define  DRM_FORMAT_RGB888 136 
#define  DRM_FORMAT_UYVY 135 
#define  DRM_FORMAT_VYUY 134 
#define  DRM_FORMAT_XRGB8888 133 
#define  DRM_FORMAT_YUV420 132 
#define  DRM_FORMAT_YUV422 131 
#define  DRM_FORMAT_YUYV 130 
#define  DRM_FORMAT_YVU420 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  EXYNOS_CIDMAPARAM ; 
 int EXYNOS_CIDMAPARAM_W_MODE_64X32 ; 
 int EXYNOS_CIDMAPARAM_W_MODE_LINEAR ; 
 int EXYNOS_CIDMAPARAM_W_MODE_MASK ; 
 int /*<<< orphan*/  EXYNOS_CIEXTEN ; 
 int EXYNOS_CIEXTEN_YUV444_OUT ; 
 int /*<<< orphan*/  EXYNOS_CITRGFMT ; 
 int EXYNOS_CITRGFMT_OUTFORMAT_MASK ; 
 int EXYNOS_CITRGFMT_OUTFORMAT_RGB ; 
 int EXYNOS_CITRGFMT_OUTFORMAT_YCBCR420 ; 
 int EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422 ; 
 int EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422_1PLANE ; 
 int /*<<< orphan*/  fimc_dst_set_fmt_order (struct fimc_context*,int) ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_dst_set_fmt(struct fimc_context *ctx, u32 fmt, bool tiled)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_read(ctx, EXYNOS_CIEXTEN);

	if (fmt == DRM_FORMAT_AYUV) {
		cfg |= EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_write(ctx, cfg, EXYNOS_CIEXTEN);
	} else {
		cfg &= ~EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_write(ctx, cfg, EXYNOS_CIEXTEN);

		cfg = fimc_read(ctx, EXYNOS_CITRGFMT);
		cfg &= ~EXYNOS_CITRGFMT_OUTFORMAT_MASK;

		switch (fmt) {
		case DRM_FORMAT_RGB565:
		case DRM_FORMAT_RGB888:
		case DRM_FORMAT_XRGB8888:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_RGB;
			break;
		case DRM_FORMAT_YUYV:
		case DRM_FORMAT_YVYU:
		case DRM_FORMAT_UYVY:
		case DRM_FORMAT_VYUY:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422_1PLANE;
			break;
		case DRM_FORMAT_NV16:
		case DRM_FORMAT_NV61:
		case DRM_FORMAT_YUV422:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422;
			break;
		case DRM_FORMAT_YUV420:
		case DRM_FORMAT_YVU420:
		case DRM_FORMAT_NV12:
		case DRM_FORMAT_NV21:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR420;
			break;
		}

		fimc_write(ctx, cfg, EXYNOS_CITRGFMT);
	}

	cfg = fimc_read(ctx, EXYNOS_CIDMAPARAM);
	cfg &= ~EXYNOS_CIDMAPARAM_W_MODE_MASK;

	if (tiled)
		cfg |= EXYNOS_CIDMAPARAM_W_MODE_64X32;
	else
		cfg |= EXYNOS_CIDMAPARAM_W_MODE_LINEAR;

	fimc_write(ctx, cfg, EXYNOS_CIDMAPARAM);

	fimc_dst_set_fmt_order(ctx, fmt);
}