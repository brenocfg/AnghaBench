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
 int EXYNOS_CITRGFMT_FLIP_MASK ; 
 int EXYNOS_CITRGFMT_FLIP_X_MIRROR ; 
 int EXYNOS_CITRGFMT_FLIP_Y_MIRROR ; 
 int EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_dst_set_transf(struct fimc_context *ctx, unsigned int rotation)
{
	unsigned int degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "rotation[0x%x]\n", rotation);

	cfg = fimc_read(ctx, EXYNOS_CITRGFMT);
	cfg &= ~EXYNOS_CITRGFMT_FLIP_MASK;
	cfg &= ~EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE;

	switch (degree) {
	case DRM_MODE_ROTATE_0:
		if (rotation & DRM_MODE_REFLECT_X)
			cfg |= EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg |= EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_90:
		cfg |= EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg |= EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg |= EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_180:
		cfg |= (EXYNOS_CITRGFMT_FLIP_X_MIRROR |
			EXYNOS_CITRGFMT_FLIP_Y_MIRROR);
		if (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		break;
	case DRM_MODE_ROTATE_270:
		cfg |= (EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE |
			EXYNOS_CITRGFMT_FLIP_X_MIRROR |
			EXYNOS_CITRGFMT_FLIP_Y_MIRROR);
		if (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		break;
	}

	fimc_write(ctx, cfg, EXYNOS_CITRGFMT);
}