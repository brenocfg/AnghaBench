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
 int /*<<< orphan*/  REG_A5XX_GPMU_PWR_COL_BINNING_CTRL ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_PWR_COL_INTER_FRAME_CTRL ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_PWR_COL_INTER_FRAME_HYST ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_PWR_COL_STAGGER_DELAY ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a5xx_pc_init(struct msm_gpu *gpu)
{
	gpu_write(gpu, REG_A5XX_GPMU_PWR_COL_INTER_FRAME_CTRL, 0x7F);
	gpu_write(gpu, REG_A5XX_GPMU_PWR_COL_BINNING_CTRL, 0);
	gpu_write(gpu, REG_A5XX_GPMU_PWR_COL_INTER_FRAME_HYST, 0xA0080);
	gpu_write(gpu, REG_A5XX_GPMU_PWR_COL_STAGGER_DELAY, 0x600040);
}