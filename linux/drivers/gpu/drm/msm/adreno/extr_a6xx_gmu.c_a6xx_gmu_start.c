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
 int /*<<< orphan*/  REG_A6XX_GMU_CM3_FW_INIT_RESULT ; 
 int /*<<< orphan*/  REG_A6XX_GMU_CM3_SYSRESET ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a6xx_gmu_start(struct a6xx_gmu *gmu)
{
	int ret;
	u32 val;

	gmu_write(gmu, REG_A6XX_GMU_CM3_SYSRESET, 1);
	gmu_write(gmu, REG_A6XX_GMU_CM3_SYSRESET, 0);

	ret = gmu_poll_timeout(gmu, REG_A6XX_GMU_CM3_FW_INIT_RESULT, val,
		val == 0xbabeface, 100, 10000);

	if (ret)
		DRM_DEV_ERROR(gmu->dev, "GMU firmware initialization timed out\n");

	return ret;
}