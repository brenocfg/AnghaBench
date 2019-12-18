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
struct a6xx_gmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE ; 
 int /*<<< orphan*/  REG_A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_0 ; 
 int /*<<< orphan*/  REG_A6XX_GMU_RSCC_CONTROL_ACK ; 
 int /*<<< orphan*/  REG_A6XX_GMU_RSCC_CONTROL_REQ ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_MASK ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_SEQ_BUSY_DRV0 ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gmu_rmw (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int a6xx_rpmh_start(struct a6xx_gmu *gmu)
{
	int ret;
	u32 val;

	gmu_write(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 1 << 1);
	/* Wait for the register to finish posting */
	wmb();

	ret = gmu_poll_timeout(gmu, REG_A6XX_GMU_RSCC_CONTROL_ACK, val,
		val & (1 << 1), 100, 10000);
	if (ret) {
		DRM_DEV_ERROR(gmu->dev, "Unable to power on the GPU RSC\n");
		return ret;
	}

	ret = gmu_poll_timeout(gmu, REG_A6XX_RSCC_SEQ_BUSY_DRV0, val,
		!val, 100, 10000);

	if (ret) {
		DRM_DEV_ERROR(gmu->dev, "GPU RSC sequence stuck while waking up the GPU\n");
		return ret;
	}

	gmu_write(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 0);

	/* Set up CX GMU counter 0 to count busy ticks */
	gmu_write(gmu, REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_MASK, 0xff000000);
	gmu_rmw(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_0, 0xff, 0x20);

	/* Enable the power counter */
	gmu_write(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE, 1);
	return 0;
}