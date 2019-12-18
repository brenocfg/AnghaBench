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
 int EFAULT ; 
 int /*<<< orphan*/  REG_A6XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a6xx_fault_handler(void *arg, unsigned long iova, int flags)
{
	struct msm_gpu *gpu = arg;

	pr_warn_ratelimited("*** gpu fault: iova=%08lx, flags=%d (%u,%u,%u,%u)\n",
			iova, flags,
			gpu_read(gpu, REG_A6XX_CP_SCRATCH_REG(4)),
			gpu_read(gpu, REG_A6XX_CP_SCRATCH_REG(5)),
			gpu_read(gpu, REG_A6XX_CP_SCRATCH_REG(6)),
			gpu_read(gpu, REG_A6XX_CP_SCRATCH_REG(7)));

	return -EFAULT;
}