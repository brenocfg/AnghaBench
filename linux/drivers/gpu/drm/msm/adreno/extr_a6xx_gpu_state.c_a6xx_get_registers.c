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
struct a6xx_gpu_state {int nr_registers; int /*<<< orphan*/ * registers; } ;
struct a6xx_crashdumper {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * a6xx_ahb_reglist ; 
 int /*<<< orphan*/  a6xx_get_ahb_gpu_registers (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a6xx_get_crashdumper_hlsq_registers (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_get_crashdumper_registers (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/ * a6xx_hlsq_reglist ; 
 int /*<<< orphan*/ * a6xx_reglist ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 

__attribute__((used)) static void a6xx_get_registers(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		struct a6xx_crashdumper *dumper)
{
	int i, count = ARRAY_SIZE(a6xx_ahb_reglist) +
		ARRAY_SIZE(a6xx_reglist) +
		ARRAY_SIZE(a6xx_hlsq_reglist);
	int index = 0;

	a6xx_state->registers = state_kcalloc(a6xx_state,
		count, sizeof(*a6xx_state->registers));

	if (!a6xx_state->registers)
		return;

	a6xx_state->nr_registers = count;

	for (i = 0; i < ARRAY_SIZE(a6xx_ahb_reglist); i++)
		a6xx_get_ahb_gpu_registers(gpu,
			a6xx_state, &a6xx_ahb_reglist[i],
			&a6xx_state->registers[index++]);

	for (i = 0; i < ARRAY_SIZE(a6xx_reglist); i++)
		a6xx_get_crashdumper_registers(gpu,
			a6xx_state, &a6xx_reglist[i],
			&a6xx_state->registers[index++],
			dumper);

	for (i = 0; i < ARRAY_SIZE(a6xx_hlsq_reglist); i++)
		a6xx_get_crashdumper_hlsq_registers(gpu,
			a6xx_state, &a6xx_hlsq_reglist[i],
			&a6xx_state->registers[index++],
			dumper);
}