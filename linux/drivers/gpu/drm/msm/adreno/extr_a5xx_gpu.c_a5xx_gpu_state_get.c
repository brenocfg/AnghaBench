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
struct msm_gpu_state {int /*<<< orphan*/  rbbm_status; } ;
struct msm_gpu {int dummy; } ;
struct a5xx_gpu_state {struct msm_gpu_state base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_gpu_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_STATUS ; 
 int /*<<< orphan*/  a5xx_gpu_state_get_hlsq_regs (struct msm_gpu*,struct a5xx_gpu_state*) ; 
 int /*<<< orphan*/  a5xx_set_hwcg (struct msm_gpu*,int) ; 
 int /*<<< orphan*/  adreno_gpu_state_get (struct msm_gpu*,struct msm_gpu_state*) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct msm_gpu_state *a5xx_gpu_state_get(struct msm_gpu *gpu)
{
	struct a5xx_gpu_state *a5xx_state = kzalloc(sizeof(*a5xx_state),
			GFP_KERNEL);

	if (!a5xx_state)
		return ERR_PTR(-ENOMEM);

	/* Temporarily disable hardware clock gating before reading the hw */
	a5xx_set_hwcg(gpu, false);

	/* First get the generic state from the adreno core */
	adreno_gpu_state_get(gpu, &(a5xx_state->base));

	a5xx_state->base.rbbm_status = gpu_read(gpu, REG_A5XX_RBBM_STATUS);

	/* Get the HLSQ regs with the help of the crashdumper */
	a5xx_gpu_state_get_hlsq_regs(gpu, a5xx_state);

	a5xx_set_hwcg(gpu, true);

	return &a5xx_state->base;
}