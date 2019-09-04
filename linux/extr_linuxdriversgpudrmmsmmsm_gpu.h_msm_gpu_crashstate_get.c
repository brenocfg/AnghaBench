#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu_state {int /*<<< orphan*/  ref; } ;
struct msm_gpu {TYPE_1__* dev; struct msm_gpu_state* crashstate; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct msm_gpu_state *msm_gpu_crashstate_get(struct msm_gpu *gpu)
{
	struct msm_gpu_state *state = NULL;

	mutex_lock(&gpu->dev->struct_mutex);

	if (gpu->crashstate) {
		kref_get(&gpu->crashstate->ref);
		state = gpu->crashstate;
	}

	mutex_unlock(&gpu->dev->struct_mutex);

	return state;
}