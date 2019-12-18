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
struct thermal_cooling_device {struct etnaviv_gpu* devdata; } ;
struct etnaviv_gpu {unsigned long freq_scale; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  etnaviv_gpu_update_clock (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
etnaviv_gpu_cooling_set_cur_state(struct thermal_cooling_device *cdev,
				  unsigned long state)
{
	struct etnaviv_gpu *gpu = cdev->devdata;

	mutex_lock(&gpu->lock);
	gpu->freq_scale = state;
	if (!pm_runtime_suspended(gpu->dev))
		etnaviv_gpu_update_clock(gpu);
	mutex_unlock(&gpu->lock);

	return 0;
}