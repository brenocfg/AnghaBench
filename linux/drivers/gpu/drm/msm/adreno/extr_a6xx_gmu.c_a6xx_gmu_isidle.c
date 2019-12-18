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
 int A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 

bool a6xx_gmu_isidle(struct a6xx_gmu *gmu)
{
	u32 reg;

	if (!gmu->initialized)
		return true;

	reg = gmu_read(gmu, REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS);

	if (reg &  A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB)
		return false;

	return true;
}