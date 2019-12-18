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
struct msm_gpu_state {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct msm_gpu_state*) ; 
 int /*<<< orphan*/  adreno_gpu_state_kref_destroy ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int adreno_gpu_state_put(struct msm_gpu_state *state)
{
	if (IS_ERR_OR_NULL(state))
		return 1;

	return kref_put(&state->ref, adreno_gpu_state_kref_destroy);
}