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
struct a6xx_gmu {int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SPTPRAC_GDSC_POWER_OFF ; 
 int A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SP_CLOCK_OFF ; 
 int /*<<< orphan*/  REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 

bool a6xx_gmu_sptprac_is_on(struct a6xx_gmu *gmu)
{
	u32 val;

	/* This can be called from gpu state code so make sure GMU is valid */
	if (!gmu->initialized)
		return false;

	val = gmu_read(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS);

	return !(val &
		(A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SPTPRAC_GDSC_POWER_OFF |
		A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SP_CLOCK_OFF));
}