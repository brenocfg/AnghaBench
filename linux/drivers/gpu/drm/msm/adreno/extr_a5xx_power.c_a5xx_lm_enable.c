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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A5XX_GDPM_INT_EN ; 
 int /*<<< orphan*/  REG_A5XX_GDPM_INT_MASK ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_CLOCK_THROTTLE_CTRL ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_GPMU_VOLTAGE_INTR_EN_MASK ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_TEMP_THRESHOLD_INTR_EN_MASK ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_THROTTLE_UNMASK_FORCE_CTRL ; 
 int /*<<< orphan*/  adreno_is_a530 (struct adreno_gpu*) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void a5xx_lm_enable(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);

	/* This init sequence only applies to A530 */
	if (!adreno_is_a530(adreno_gpu))
		return;

	gpu_write(gpu, REG_A5XX_GDPM_INT_MASK, 0x0);
	gpu_write(gpu, REG_A5XX_GDPM_INT_EN, 0x0A);
	gpu_write(gpu, REG_A5XX_GPMU_GPMU_VOLTAGE_INTR_EN_MASK, 0x01);
	gpu_write(gpu, REG_A5XX_GPMU_TEMP_THRESHOLD_INTR_EN_MASK, 0x50000);
	gpu_write(gpu, REG_A5XX_GPMU_THROTTLE_UNMASK_FORCE_CTRL, 0x30000);

	gpu_write(gpu, REG_A5XX_GPMU_CLOCK_THROTTLE_CTRL, 0x011);
}