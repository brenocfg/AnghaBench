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
struct a6xx_gmu {int idle_level; } ;

/* Variables and functions */
 int GMU_IDLE_STATE_IFPC ; 
 int GMU_IDLE_STATE_SPTP ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE ; 
 int /*<<< orphan*/  a6xx_gmu_gx_is_on (struct a6xx_gmu*) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool a6xx_gmu_check_idle_level(struct a6xx_gmu *gmu)
{
	u32 val;
	int local = gmu->idle_level;

	/* SPTP and IFPC both report as IFPC */
	if (gmu->idle_level == GMU_IDLE_STATE_SPTP)
		local = GMU_IDLE_STATE_IFPC;

	val = gmu_read(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE);

	if (val == local) {
		if (gmu->idle_level != GMU_IDLE_STATE_IFPC ||
			!a6xx_gmu_gx_is_on(gmu))
			return true;
	}

	return false;
}