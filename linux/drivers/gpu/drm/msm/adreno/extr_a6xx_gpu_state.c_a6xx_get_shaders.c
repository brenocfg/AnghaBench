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
struct a6xx_gpu_state {int nr_shaders; int /*<<< orphan*/ * shaders; } ;
struct a6xx_crashdumper {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a6xx_get_shader_block (struct msm_gpu*,struct a6xx_gpu_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/ * a6xx_shader_blocks ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 

__attribute__((used)) static void a6xx_get_shaders(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		struct a6xx_crashdumper *dumper)
{
	int i;

	a6xx_state->shaders = state_kcalloc(a6xx_state,
		ARRAY_SIZE(a6xx_shader_blocks), sizeof(*a6xx_state->shaders));

	if (!a6xx_state->shaders)
		return;

	a6xx_state->nr_shaders = ARRAY_SIZE(a6xx_shader_blocks);

	for (i = 0; i < ARRAY_SIZE(a6xx_shader_blocks); i++)
		a6xx_get_shader_block(gpu, a6xx_state, &a6xx_shader_blocks[i],
			&a6xx_state->shaders[i], dumper);
}