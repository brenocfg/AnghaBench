#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {TYPE_2__* dev; int /*<<< orphan*/ * crashstate; TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_3__ {scalar_t__ (* gpu_state_put ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void msm_gpu_crashstate_put(struct msm_gpu *gpu)
{
	mutex_lock(&gpu->dev->struct_mutex);

	if (gpu->crashstate) {
		if (gpu->funcs->gpu_state_put(gpu->crashstate))
			gpu->crashstate = NULL;
	}

	mutex_unlock(&gpu->dev->struct_mutex);
}