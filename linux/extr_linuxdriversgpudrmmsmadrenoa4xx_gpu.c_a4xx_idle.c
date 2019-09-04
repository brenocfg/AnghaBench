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
struct msm_gpu {int /*<<< orphan*/  name; int /*<<< orphan*/ * rb; } ;

/* Variables and functions */
 int A4XX_RBBM_STATUS_GPU_BUSY ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_A4XX_RBBM_STATUS ; 
 int /*<<< orphan*/  adreno_idle (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ spin_until (int) ; 

__attribute__((used)) static bool a4xx_idle(struct msm_gpu *gpu)
{
	/* wait for ringbuffer to drain: */
	if (!adreno_idle(gpu, gpu->rb[0]))
		return false;

	/* then wait for GPU to finish: */
	if (spin_until(!(gpu_read(gpu, REG_A4XX_RBBM_STATUS) &
					A4XX_RBBM_STATUS_GPU_BUSY))) {
		DRM_ERROR("%s: timeout waiting for GPU to idle!\n", gpu->name);
		/* TODO maybe we need to reset GPU here to recover from hang? */
		return false;
	}

	return true;
}