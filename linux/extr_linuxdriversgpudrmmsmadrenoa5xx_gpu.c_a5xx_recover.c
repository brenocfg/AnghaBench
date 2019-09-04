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
 int /*<<< orphan*/  REG_A5XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_SW_RESET_CMD ; 
 int /*<<< orphan*/  a5xx_dump (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_dump_info (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_recover (struct msm_gpu*) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hang_debug ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a5xx_recover(struct msm_gpu *gpu)
{
	int i;

	adreno_dump_info(gpu);

	for (i = 0; i < 8; i++) {
		printk("CP_SCRATCH_REG%d: %u\n", i,
			gpu_read(gpu, REG_A5XX_CP_SCRATCH_REG(i)));
	}

	if (hang_debug)
		a5xx_dump(gpu);

	gpu_write(gpu, REG_A5XX_RBBM_SW_RESET_CMD, 1);
	gpu_read(gpu, REG_A5XX_RBBM_SW_RESET_CMD);
	gpu_write(gpu, REG_A5XX_RBBM_SW_RESET_CMD, 0);
	adreno_recover(gpu);
}