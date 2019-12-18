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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_registers {int count; scalar_t__* registers; } ;
struct a6xx_gpu_state_obj {int /*<<< orphan*/ * data; void const* handle; } ;
struct a6xx_gpu_state {int dummy; } ;
struct a6xx_gmu {int dummy; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int RANGE (scalar_t__*,int) ; 
 int /*<<< orphan*/  gmu_read (struct a6xx_gmu*,scalar_t__) ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void _a6xx_get_gmu_registers(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		const struct a6xx_registers *regs,
		struct a6xx_gpu_state_obj *obj)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int i, regcount = 0, index = 0;

	for (i = 0; i < regs->count; i += 2)
		regcount += RANGE(regs->registers, i);

	obj->handle = (const void *) regs;
	obj->data = state_kcalloc(a6xx_state, regcount, sizeof(u32));
	if (!obj->data)
		return;

	for (i = 0; i < regs->count; i += 2) {
		u32 count = RANGE(regs->registers, i);
		int j;

		for (j = 0; j < count; j++)
			obj->data[index++] = gmu_read(gmu,
				regs->registers[i] + j);
	}
}