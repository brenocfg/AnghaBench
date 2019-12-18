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
 int /*<<< orphan*/  REG_A5XX_RBBM_BLOCK_SW_RESET_CMD ; 
 int /*<<< orphan*/  REG_A5XX_VBIF_XIN_HALT_CTRL0 ; 
 int /*<<< orphan*/  REG_A5XX_VBIF_XIN_HALT_CTRL1 ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int msm_gpu_pm_suspend (struct msm_gpu*) ; 
 int /*<<< orphan*/  spin_until (int) ; 

__attribute__((used)) static int a5xx_pm_suspend(struct msm_gpu *gpu)
{
	/* Clear the VBIF pipe before shutting down */
	gpu_write(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL0, 0xF);
	spin_until((gpu_read(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL1) & 0xF) == 0xF);

	gpu_write(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL0, 0);

	/*
	 * Reset the VBIF before power collapse to avoid issue with FIFO
	 * entries
	 */
	gpu_write(gpu, REG_A5XX_RBBM_BLOCK_SW_RESET_CMD, 0x003C0000);
	gpu_write(gpu, REG_A5XX_RBBM_BLOCK_SW_RESET_CMD, 0x00000000);

	return msm_gpu_pm_suspend(gpu);
}