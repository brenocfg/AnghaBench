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
typedef  int /*<<< orphan*/  u32 ;
struct msm_gpu {int dummy; } ;
struct a6xx_gpu_state {int nr_indexed_regs; TYPE_1__* indexed_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_A6XX_CP_MEM_POOL_SIZE ; 
 int /*<<< orphan*/  a6xx_cp_mempool_indexed ; 
 int /*<<< orphan*/  a6xx_get_indexed_regs (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * a6xx_indexed_reglist ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* state_kcalloc (struct a6xx_gpu_state*,int,int) ; 

__attribute__((used)) static void a6xx_get_indexed_registers(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state)
{
	u32 mempool_size;
	int count = ARRAY_SIZE(a6xx_indexed_reglist) + 1;
	int i;

	a6xx_state->indexed_regs = state_kcalloc(a6xx_state, count,
		sizeof(a6xx_state->indexed_regs));
	if (!a6xx_state->indexed_regs)
		return;

	for (i = 0; i < ARRAY_SIZE(a6xx_indexed_reglist); i++)
		a6xx_get_indexed_regs(gpu, a6xx_state, &a6xx_indexed_reglist[i],
			&a6xx_state->indexed_regs[i]);

	/* Set the CP mempool size to 0 to stabilize it while dumping */
	mempool_size = gpu_read(gpu, REG_A6XX_CP_MEM_POOL_SIZE);
	gpu_write(gpu, REG_A6XX_CP_MEM_POOL_SIZE, 0);

	/* Get the contents of the CP mempool */
	a6xx_get_indexed_regs(gpu, a6xx_state, &a6xx_cp_mempool_indexed,
		&a6xx_state->indexed_regs[i]);

	/*
	 * Offset 0x2000 in the mempool is the size - copy the saved size over
	 * so the data is consistent
	 */
	a6xx_state->indexed_regs[i].data[0x2000] = mempool_size;

	/* Restore the size in the hardware */
	gpu_write(gpu, REG_A6XX_CP_MEM_POOL_SIZE, mempool_size);

	a6xx_state->nr_indexed_regs = count;
}