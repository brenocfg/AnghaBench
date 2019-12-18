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
#define  DRM_FORMAT_NV12 142 
#define  DRM_FORMAT_NV16 141 
#define  DRM_FORMAT_NV21 140 
#define  DRM_FORMAT_NV61 139 
#define  DRM_FORMAT_RGB565 138 
#define  DRM_FORMAT_RGB888 137 
#define  DRM_FORMAT_UYVY 136 
#define  DRM_FORMAT_VYUY 135 
#define  DRM_FORMAT_XRGB8888 134 
#define  DRM_FORMAT_YUV420 133 
#define  DRM_FORMAT_YUV422 132 
#define  DRM_FORMAT_YUV444 131 
#define  DRM_FORMAT_YUYV 130 
#define  DRM_FORMAT_YVU420 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  EXYNOS_CIDMAPARAM ; 
 int EXYNOS_CIDMAPARAM_R_MODE_64X32 ; 
 int EXYNOS_CIDMAPARAM_R_MODE_LINEAR ; 
 int EXYNOS_CIDMAPARAM_R_MODE_MASK ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL ; 
 int EXYNOS_MSCTRL_INFORMAT_RGB ; 
 int EXYNOS_MSCTRL_INFORMAT_YCBCR420 ; 
 int EXYNOS_MSCTRL_INFORMAT_YCBCR422 ; 
 int EXYNOS_MSCTRL_INFORMAT_YCBCR422_1PLANE ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_src_set_fmt_order (struct fimc_context*,int) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_src_set_fmt(struct fimc_context *ctx, u32 fmt, bool tiled)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_read(ctx, EXYNOS_MSCTRL);
	cfg &= ~EXYNOS_MSCTRL_INFORMAT_RGB;

	switch (fmt) {
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_XRGB8888:
		cfg |= EXYNOS_MSCTRL_INFORMAT_RGB;
		break;
	case DRM_FORMAT_YUV444:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR420;
		break;
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR422_1PLANE;
		break;
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV61:
	case DRM_FORMAT_YUV422:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR422;
		break;
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV21:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR420;
		break;
	}

	fimc_write(ctx, cfg, EXYNOS_MSCTRL);

	cfg = fimc_read(ctx, EXYNOS_CIDMAPARAM);
	cfg &= ~EXYNOS_CIDMAPARAM_R_MODE_MASK;

	if (tiled)
		cfg |= EXYNOS_CIDMAPARAM_R_MODE_64X32;
	else
		cfg |= EXYNOS_CIDMAPARAM_R_MODE_LINEAR;

	fimc_write(ctx, cfg, EXYNOS_CIDMAPARAM);

	fimc_src_set_fmt_order(ctx, fmt);
}