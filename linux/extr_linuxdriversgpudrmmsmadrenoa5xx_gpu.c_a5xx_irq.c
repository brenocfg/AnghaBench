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
typedef  int u32 ;
struct msm_gpu {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int A5XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS ; 
 int A5XX_RBBM_INT_0_MASK_CP_HW_ERROR ; 
 int A5XX_RBBM_INT_0_MASK_CP_SW ; 
 int A5XX_RBBM_INT_0_MASK_GPMU_VOLTAGE_DROOP ; 
 int A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR ; 
 int A5XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RBBM_ERROR_MASK ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_INT_0_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_INT_CLEAR_CMD ; 
 int /*<<< orphan*/  a5xx_cp_err_irq (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_fault_detect_irq (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_gpmu_err_irq (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_preempt_irq (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_preempt_trigger (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_rbbm_err_irq (struct msm_gpu*,int) ; 
 int /*<<< orphan*/  a5xx_uche_err_irq (struct msm_gpu*) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_gpu_retire (struct msm_gpu*) ; 

__attribute__((used)) static irqreturn_t a5xx_irq(struct msm_gpu *gpu)
{
	u32 status = gpu_read(gpu, REG_A5XX_RBBM_INT_0_STATUS);

	/*
	 * Clear all the interrupts except RBBM_AHB_ERROR - if we clear it
	 * before the source is cleared the interrupt will storm.
	 */
	gpu_write(gpu, REG_A5XX_RBBM_INT_CLEAR_CMD,
		status & ~A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR);

	/* Pass status to a5xx_rbbm_err_irq because we've already cleared it */
	if (status & RBBM_ERROR_MASK)
		a5xx_rbbm_err_irq(gpu, status);

	if (status & A5XX_RBBM_INT_0_MASK_CP_HW_ERROR)
		a5xx_cp_err_irq(gpu);

	if (status & A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT)
		a5xx_fault_detect_irq(gpu);

	if (status & A5XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS)
		a5xx_uche_err_irq(gpu);

	if (status & A5XX_RBBM_INT_0_MASK_GPMU_VOLTAGE_DROOP)
		a5xx_gpmu_err_irq(gpu);

	if (status & A5XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS) {
		a5xx_preempt_trigger(gpu);
		msm_gpu_retire(gpu);
	}

	if (status & A5XX_RBBM_INT_0_MASK_CP_SW)
		a5xx_preempt_irq(gpu);

	return IRQ_HANDLED;
}