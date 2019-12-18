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
 int /*<<< orphan*/  REG_A4XX_RBBM_STATUS ; 
 int /*<<< orphan*/  adreno_dump (struct msm_gpu*) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a4xx_dump(struct msm_gpu *gpu)
{
	printk("status:   %08x\n",
			gpu_read(gpu, REG_A4XX_RBBM_STATUS));
	adreno_dump(gpu);
}