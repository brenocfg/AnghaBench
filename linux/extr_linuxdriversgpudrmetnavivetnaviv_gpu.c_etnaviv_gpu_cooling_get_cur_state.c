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
struct etnaviv_gpu {unsigned long freq_scale; } ;

/* Variables and functions */

__attribute__((used)) static int
etnaviv_gpu_cooling_get_cur_state(struct thermal_cooling_device *cdev,
				  unsigned long *state)
{
	struct etnaviv_gpu *gpu = cdev->devdata;

	*state = gpu->freq_scale;

	return 0;
}