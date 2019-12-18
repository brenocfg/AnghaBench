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
struct fimc_context {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXYNOS_CISTATUS ; 
 int EXYNOS_CISTATUS_OVFICB ; 
 int EXYNOS_CISTATUS_OVFICR ; 
 int EXYNOS_CISTATUS_OVFIY ; 
 int /*<<< orphan*/  EXYNOS_CIWDOFST ; 
 int EXYNOS_CIWDOFST_CLROVFICB ; 
 int EXYNOS_CIWDOFST_CLROVFICR ; 
 int EXYNOS_CIWDOFST_CLROVFIY ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_set_bits (struct fimc_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool fimc_check_ovf(struct fimc_context *ctx)
{
	u32 status, flag;

	status = fimc_read(ctx, EXYNOS_CISTATUS);
	flag = EXYNOS_CISTATUS_OVFIY | EXYNOS_CISTATUS_OVFICB |
		EXYNOS_CISTATUS_OVFICR;

	DRM_DEV_DEBUG_KMS(ctx->dev, "flag[0x%x]\n", flag);

	if (status & flag) {
		fimc_set_bits(ctx, EXYNOS_CIWDOFST,
			EXYNOS_CIWDOFST_CLROVFIY | EXYNOS_CIWDOFST_CLROVFICB |
			EXYNOS_CIWDOFST_CLROVFICR);

		DRM_DEV_ERROR(ctx->dev,
			      "occurred overflow at %d, status 0x%x.\n",
			      ctx->id, status);
		return true;
	}

	return false;
}