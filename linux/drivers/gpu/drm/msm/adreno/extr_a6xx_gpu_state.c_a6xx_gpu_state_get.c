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
struct msm_gpu_state {int dummy; } ;
struct msm_gpu {int /*<<< orphan*/  aspace; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu_state {struct msm_gpu_state base; int /*<<< orphan*/  objs; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;
struct a6xx_crashdumper {int /*<<< orphan*/  bo; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_gpu_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a6xx_crashdumper_init (struct msm_gpu*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_get_clusters (struct msm_gpu*,struct a6xx_gpu_state*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_get_dbgahb_clusters (struct msm_gpu*,struct a6xx_gpu_state*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_get_debugbus (struct msm_gpu*,struct a6xx_gpu_state*) ; 
 int /*<<< orphan*/  a6xx_get_gmu_registers (struct msm_gpu*,struct a6xx_gpu_state*) ; 
 int /*<<< orphan*/  a6xx_get_indexed_registers (struct msm_gpu*,struct a6xx_gpu_state*) ; 
 int /*<<< orphan*/  a6xx_get_registers (struct msm_gpu*,struct a6xx_gpu_state*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_get_shaders (struct msm_gpu*,struct a6xx_gpu_state*,struct a6xx_crashdumper*) ; 
 int /*<<< orphan*/  a6xx_gmu_gx_is_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adreno_gpu_state_get (struct msm_gpu*,struct msm_gpu_state*) ; 
 struct a6xx_gpu_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_kernel_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

struct msm_gpu_state *a6xx_gpu_state_get(struct msm_gpu *gpu)
{
	struct a6xx_crashdumper dumper = { 0 };
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	struct a6xx_gpu_state *a6xx_state = kzalloc(sizeof(*a6xx_state),
		GFP_KERNEL);

	if (!a6xx_state)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&a6xx_state->objs);

	/* Get the generic state from the adreno core */
	adreno_gpu_state_get(gpu, &a6xx_state->base);

	a6xx_get_gmu_registers(gpu, a6xx_state);

	/* If GX isn't on the rest of the data isn't going to be accessible */
	if (!a6xx_gmu_gx_is_on(&a6xx_gpu->gmu))
		return &a6xx_state->base;

	/* Get the banks of indexed registers */
	a6xx_get_indexed_registers(gpu, a6xx_state);

	/* Try to initialize the crashdumper */
	if (!a6xx_crashdumper_init(gpu, &dumper)) {
		a6xx_get_registers(gpu, a6xx_state, &dumper);
		a6xx_get_shaders(gpu, a6xx_state, &dumper);
		a6xx_get_clusters(gpu, a6xx_state, &dumper);
		a6xx_get_dbgahb_clusters(gpu, a6xx_state, &dumper);

		msm_gem_kernel_put(dumper.bo, gpu->aspace, true);
	}

	a6xx_get_debugbus(gpu, a6xx_state);

	return  &a6xx_state->base;
}