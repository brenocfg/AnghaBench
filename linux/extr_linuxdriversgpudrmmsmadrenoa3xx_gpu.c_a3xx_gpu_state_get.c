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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_gpu_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REG_A3XX_RBBM_STATUS ; 
 int /*<<< orphan*/  adreno_gpu_state_get (struct msm_gpu*,struct msm_gpu_state*) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 struct msm_gpu_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct msm_gpu_state *a3xx_gpu_state_get(struct msm_gpu *gpu)
{
	struct msm_gpu_state *state = kzalloc(sizeof(*state), GFP_KERNEL);

	if (!state)
		return ERR_PTR(-ENOMEM);

	adreno_gpu_state_get(gpu, state);

	state->rbbm_status = gpu_read(gpu, REG_A3XX_RBBM_STATUS);

	return state;
}