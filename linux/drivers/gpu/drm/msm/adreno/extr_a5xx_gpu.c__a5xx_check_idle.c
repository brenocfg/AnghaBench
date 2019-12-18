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

/* Variables and functions */
 int A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT ; 
 int A5XX_RBBM_STATUS_HI_BUSY ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_INT_0_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_STATUS ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool _a5xx_check_idle(struct msm_gpu *gpu)
{
	if (gpu_read(gpu, REG_A5XX_RBBM_STATUS) & ~A5XX_RBBM_STATUS_HI_BUSY)
		return false;

	/*
	 * Nearly every abnormality ends up pausing the GPU and triggering a
	 * fault so we can safely just watch for this one interrupt to fire
	 */
	return !(gpu_read(gpu, REG_A5XX_RBBM_INT_0_STATUS) &
		A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT);
}