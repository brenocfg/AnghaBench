#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gpu {int fast_rate; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int lm_leakage; } ;
struct TYPE_3__ {int value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_INIT_MSG_MAGIC ; 
 int AGC_INIT_MSG_VALUE ; 
 int /*<<< orphan*/  AGC_MSG_COMMAND ; 
 int /*<<< orphan*/  AGC_MSG_PAYLOAD (int) ; 
 int /*<<< orphan*/  AGC_MSG_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  AGC_MSG_STATE ; 
 int AGC_POWER_CONFIG_PRODUCTION_ID ; 
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_A5XX_GDPM_CONFIG1 ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_BASE_LEAKAGE ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_BEC_ENABLE ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_DELTA_TEMP_THRESHOLD ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_GPMU_PWR_THRESHOLD ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_GPMU_VOLTAGE ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_TEMP_SENSOR_CONFIG ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_TEMP_SENSOR_ID ; 
 int _get_mvolts (struct msm_gpu*,int) ; 
 TYPE_1__* a5xx_sequence_regs ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void a530_lm_setup(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	unsigned int i;

	/* Write the block of sequence registers */
	for (i = 0; i < ARRAY_SIZE(a5xx_sequence_regs); i++)
		gpu_write(gpu, a5xx_sequence_regs[i].reg,
			a5xx_sequence_regs[i].value);

	/* Hard code the A530 GPU thermal sensor ID for the GPMU */
	gpu_write(gpu, REG_A5XX_GPMU_TEMP_SENSOR_ID, 0x60007);
	gpu_write(gpu, REG_A5XX_GPMU_DELTA_TEMP_THRESHOLD, 0x01);
	gpu_write(gpu, REG_A5XX_GPMU_TEMP_SENSOR_CONFIG, 0x01);

	/* Until we get clock scaling 0 is always the active power level */
	gpu_write(gpu, REG_A5XX_GPMU_GPMU_VOLTAGE, 0x80000000 | 0);

	gpu_write(gpu, REG_A5XX_GPMU_BASE_LEAKAGE, a5xx_gpu->lm_leakage);

	/* The threshold is fixed at 6000 for A530 */
	gpu_write(gpu, REG_A5XX_GPMU_GPMU_PWR_THRESHOLD, 0x80000000 | 6000);

	gpu_write(gpu, REG_A5XX_GPMU_BEC_ENABLE, 0x10001FFF);
	gpu_write(gpu, REG_A5XX_GDPM_CONFIG1, 0x00201FF1);

	/* Write the voltage table */
	gpu_write(gpu, REG_A5XX_GPMU_BEC_ENABLE, 0x10001FFF);
	gpu_write(gpu, REG_A5XX_GDPM_CONFIG1, 0x201FF1);

	gpu_write(gpu, AGC_MSG_STATE, 1);
	gpu_write(gpu, AGC_MSG_COMMAND, AGC_POWER_CONFIG_PRODUCTION_ID);

	/* Write the max power - hard coded to 5448 for A530 */
	gpu_write(gpu, AGC_MSG_PAYLOAD(0), 5448);
	gpu_write(gpu, AGC_MSG_PAYLOAD(1), 1);

	/*
	 * For now just write the one voltage level - we will do more when we
	 * can do scaling
	 */
	gpu_write(gpu, AGC_MSG_PAYLOAD(2), _get_mvolts(gpu, gpu->fast_rate));
	gpu_write(gpu, AGC_MSG_PAYLOAD(3), gpu->fast_rate / 1000000);

	gpu_write(gpu, AGC_MSG_PAYLOAD_SIZE, 4 * sizeof(uint32_t));
	gpu_write(gpu, AGC_INIT_MSG_MAGIC, AGC_INIT_MSG_VALUE);
}