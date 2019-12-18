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
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GX_SPTPRAC_POWER_CONTROL ; 
 int /*<<< orphan*/  REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_GPU_CC_GX_GDSCR ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_rmw (struct a6xx_gmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a6xx_sptprac_disable(struct a6xx_gmu *gmu)
{
	u32 val;
	int ret;

	/* Make sure retention is on */
	gmu_rmw(gmu, REG_A6XX_GPU_CC_GX_GDSCR, 0, (1 << 11));

	gmu_write(gmu, REG_A6XX_GMU_GX_SPTPRAC_POWER_CONTROL, 0x778001);

	ret = gmu_poll_timeout(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS, val,
		(val & 0x04), 100, 10000);

	if (ret)
		DRM_DEV_ERROR(gmu->dev, "failed to power off SPTPRAC: 0x%x\n",
			gmu_read(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS));
}