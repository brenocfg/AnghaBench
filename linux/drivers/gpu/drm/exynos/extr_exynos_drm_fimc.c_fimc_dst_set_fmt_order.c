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
 int /*<<< orphan*/  EXYNOS_CIOCTRL ; 
 int EXYNOS_CIOCTRL_ALPHA_OUT ; 
 int EXYNOS_CIOCTRL_ORDER2P_LSB_CBCR ; 
 int EXYNOS_CIOCTRL_ORDER2P_LSB_CRCB ; 
 int EXYNOS_CIOCTRL_ORDER2P_MASK ; 
 int EXYNOS_CIOCTRL_ORDER422_CBYCRY ; 
 int EXYNOS_CIOCTRL_ORDER422_CRYCBY ; 
 int EXYNOS_CIOCTRL_ORDER422_MASK ; 
 int EXYNOS_CIOCTRL_ORDER422_YCBYCR ; 
 int EXYNOS_CIOCTRL_ORDER422_YCRYCB ; 
 int EXYNOS_CIOCTRL_YCBCR_2PLANE ; 
 int EXYNOS_CIOCTRL_YCBCR_3PLANE ; 
 int EXYNOS_CIOCTRL_YCBCR_PLANE_MASK ; 
 int /*<<< orphan*/  EXYNOS_CISCCTRL ; 
 int EXYNOS_CISCCTRL_EXTRGB_EXTENSION ; 
 int EXYNOS_CISCCTRL_OUTRGB_FMT_RGB565 ; 
 int EXYNOS_CISCCTRL_OUTRGB_FMT_RGB888 ; 
 int EXYNOS_CISCCTRL_OUTRGB_FMT_RGB_MASK ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_dst_set_fmt_order(struct fimc_context *ctx, u32 fmt)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	/* RGB */
	cfg = fimc_read(ctx, EXYNOS_CISCCTRL);
	cfg &= ~EXYNOS_CISCCTRL_OUTRGB_FMT_RGB_MASK;

	switch (fmt) {
	case DRM_FORMAT_RGB565:
		cfg |= EXYNOS_CISCCTRL_OUTRGB_FMT_RGB565;
		fimc_write(ctx, cfg, EXYNOS_CISCCTRL);
		return;
	case DRM_FORMAT_RGB888:
		cfg |= EXYNOS_CISCCTRL_OUTRGB_FMT_RGB888;
		fimc_write(ctx, cfg, EXYNOS_CISCCTRL);
		return;
	case DRM_FORMAT_XRGB8888:
		cfg |= (EXYNOS_CISCCTRL_OUTRGB_FMT_RGB888 |
			EXYNOS_CISCCTRL_EXTRGB_EXTENSION);
		fimc_write(ctx, cfg, EXYNOS_CISCCTRL);
		break;
	default:
		/* bypass */
		break;
	}

	/* YUV */
	cfg = fimc_read(ctx, EXYNOS_CIOCTRL);
	cfg &= ~(EXYNOS_CIOCTRL_ORDER2P_MASK |
		EXYNOS_CIOCTRL_ORDER422_MASK |
		EXYNOS_CIOCTRL_YCBCR_PLANE_MASK);

	switch (fmt) {
	case DRM_FORMAT_XRGB8888:
		cfg |= EXYNOS_CIOCTRL_ALPHA_OUT;
		break;
	case DRM_FORMAT_YUYV:
		cfg |= EXYNOS_CIOCTRL_ORDER422_YCBYCR;
		break;
	case DRM_FORMAT_YVYU:
		cfg |= EXYNOS_CIOCTRL_ORDER422_YCRYCB;
		break;
	case DRM_FORMAT_UYVY:
		cfg |= EXYNOS_CIOCTRL_ORDER422_CBYCRY;
		break;
	case DRM_FORMAT_VYUY:
		cfg |= EXYNOS_CIOCTRL_ORDER422_CRYCBY;
		break;
	case DRM_FORMAT_NV21:
	case DRM_FORMAT_NV61:
		cfg |= EXYNOS_CIOCTRL_ORDER2P_LSB_CRCB;
		cfg |= EXYNOS_CIOCTRL_YCBCR_2PLANE;
		break;
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
		cfg |= EXYNOS_CIOCTRL_YCBCR_3PLANE;
		break;
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV16:
		cfg |= EXYNOS_CIOCTRL_ORDER2P_LSB_CBCR;
		cfg |= EXYNOS_CIOCTRL_YCBCR_2PLANE;
		break;
	}

	fimc_write(ctx, cfg, EXYNOS_CIOCTRL);
}