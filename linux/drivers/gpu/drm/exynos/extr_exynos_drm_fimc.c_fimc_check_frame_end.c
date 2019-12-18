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
 int /*<<< orphan*/  EXYNOS_CISTATUS ; 
 int EXYNOS_CISTATUS_FRAMEEND ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fimc_check_frame_end(struct fimc_context *ctx)
{
	u32 cfg;

	cfg = fimc_read(ctx, EXYNOS_CISTATUS);

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]\n", cfg);

	if (!(cfg & EXYNOS_CISTATUS_FRAMEEND))
		return false;

	cfg &= ~(EXYNOS_CISTATUS_FRAMEEND);
	fimc_write(ctx, cfg, EXYNOS_CISTATUS);

	return true;
}