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
struct a6xx_gpu_state {int nr_gmu_registers; int /*<<< orphan*/ * gmu_registers; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A6XX_GMU_AO_AHB_FENCE_CTRL ; 
 int /*<<< orphan*/  _a6xx_get_gmu_registers (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a6xx_gmu_gx_is_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * a6xx_gmu_reglist ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void a6xx_get_gmu_registers(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	a6xx_state->gmu_registers = state_kcalloc(a6xx_state,
		2, sizeof(*a6xx_state->gmu_registers));

	if (!a6xx_state->gmu_registers)
		return;

	a6xx_state->nr_gmu_registers = 2;

	/* Get the CX GMU registers from AHB */
	_a6xx_get_gmu_registers(gpu, a6xx_state, &a6xx_gmu_reglist[0],
		&a6xx_state->gmu_registers[0]);

	if (!a6xx_gmu_gx_is_on(&a6xx_gpu->gmu))
		return;

	/* Set the fence to ALLOW mode so we can access the registers */
	gpu_write(gpu, REG_A6XX_GMU_AO_AHB_FENCE_CTRL, 0);

	_a6xx_get_gmu_registers(gpu, a6xx_state, &a6xx_gmu_reglist[1],
		&a6xx_state->gmu_registers[1]);
}