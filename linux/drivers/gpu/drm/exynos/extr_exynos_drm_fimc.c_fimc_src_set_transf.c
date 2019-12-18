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
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 unsigned int DRM_MODE_ROTATE_MASK ; 
 int /*<<< orphan*/  EXYNOS_CITRGFMT ; 
 int EXYNOS_CITRGFMT_INROT90_CLOCKWISE ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL ; 
 int EXYNOS_MSCTRL_FLIP_X_MIRROR ; 
 int EXYNOS_MSCTRL_FLIP_Y_MIRROR ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_src_set_transf(struct fimc_context *ctx, unsigned int rotation)
{
	unsigned int degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg1, cfg2;

	DRM_DEV_DEBUG_KMS(ctx->dev, "rotation[%x]\n", rotation);

	cfg1 = fimc_read(ctx, EXYNOS_MSCTRL);
	cfg1 &= ~(EXYNOS_MSCTRL_FLIP_X_MIRROR |
		EXYNOS_MSCTRL_FLIP_Y_MIRROR);

	cfg2 = fimc_read(ctx, EXYNOS_CITRGFMT);
	cfg2 &= ~EXYNOS_CITRGFMT_INROT90_CLOCKWISE;

	switch (degree) {
	case DRM_MODE_ROTATE_0:
		if (rotation & DRM_MODE_REFLECT_X)
			cfg1 |= EXYNOS_MSCTRL_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg1 |= EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_90:
		cfg2 |= EXYNOS_CITRGFMT_INROT90_CLOCKWISE;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg1 |= EXYNOS_MSCTRL_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg1 |= EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_180:
		cfg1 |= (EXYNOS_MSCTRL_FLIP_X_MIRROR |
			EXYNOS_MSCTRL_FLIP_Y_MIRROR);
		if (rotation & DRM_MODE_REFLECT_X)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_270:
		cfg1 |= (EXYNOS_MSCTRL_FLIP_X_MIRROR |
			EXYNOS_MSCTRL_FLIP_Y_MIRROR);
		cfg2 |= EXYNOS_CITRGFMT_INROT90_CLOCKWISE;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		break;
	}

	fimc_write(ctx, cfg1, EXYNOS_MSCTRL);
	fimc_write(ctx, cfg2, EXYNOS_CITRGFMT);
}