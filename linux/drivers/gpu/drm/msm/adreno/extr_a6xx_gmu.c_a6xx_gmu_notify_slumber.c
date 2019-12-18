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
struct a6xx_gmu {scalar_t__ idle_level; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int ETIMEDOUT ; 
 scalar_t__ GMU_IDLE_STATE_SPTP ; 
 int /*<<< orphan*/  GMU_OOB_BOOT_SLUMBER ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_AHB_FENCE_CTRL ; 
 int /*<<< orphan*/  REG_A6XX_GMU_BOOT_SLUMBER_OPTION ; 
 int /*<<< orphan*/  REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int a6xx_gmu_set_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_sptprac_disable (struct a6xx_gmu*) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a6xx_gmu_notify_slumber(struct a6xx_gmu *gmu)
{
	int ret;

	/* Disable the power counter so the GMU isn't busy */
	gmu_write(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE, 0);

	/* Disable SPTP_PC if the CPU is responsible for it */
	if (gmu->idle_level < GMU_IDLE_STATE_SPTP)
		a6xx_sptprac_disable(gmu);

	/* Tell the GMU to get ready to slumber */
	gmu_write(gmu, REG_A6XX_GMU_BOOT_SLUMBER_OPTION, 1);

	ret = a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SLUMBER);
	a6xx_gmu_clear_oob(gmu, GMU_OOB_BOOT_SLUMBER);

	if (!ret) {
		/* Check to see if the GMU really did slumber */
		if (gmu_read(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE)
			!= 0x0f) {
			DRM_DEV_ERROR(gmu->dev, "The GMU did not go into slumber\n");
			ret = -ETIMEDOUT;
		}
	}

	/* Put fence into allow mode */
	gmu_write(gmu, REG_A6XX_GMU_AO_AHB_FENCE_CTRL, 0);
	return ret;
}