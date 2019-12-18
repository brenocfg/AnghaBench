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
struct a6xx_gmu {int dummy; } ;
typedef  enum a6xx_gmu_oob_state { ____Placeholder_a6xx_gmu_oob_state } a6xx_gmu_oob_state ;

/* Variables and functions */
#define  GMU_OOB_BOOT_SLUMBER 130 
 int GMU_OOB_BOOT_SLUMBER_CLEAR ; 
 int GMU_OOB_DCVS_CLEAR ; 
#define  GMU_OOB_DCVS_SET 129 
#define  GMU_OOB_GPU_SET 128 
 int GMU_OOB_GPU_SET_CLEAR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_HOST2GMU_INTR_SET ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

void a6xx_gmu_clear_oob(struct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state)
{
	switch (state) {
	case GMU_OOB_GPU_SET:
		gmu_write(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET,
			1 << GMU_OOB_GPU_SET_CLEAR);
		break;
	case GMU_OOB_BOOT_SLUMBER:
		gmu_write(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET,
			1 << GMU_OOB_BOOT_SLUMBER_CLEAR);
		break;
	case GMU_OOB_DCVS_SET:
		gmu_write(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET,
			1 << GMU_OOB_DCVS_CLEAR);
		break;
	}
}