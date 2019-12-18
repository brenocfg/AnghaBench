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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_gpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A5XX_RBBM_PERFCTR_CP_0_HI ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_PERFCTR_CP_0_LO ; 
 int /*<<< orphan*/  gpu_read64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a5xx_get_timestamp(struct msm_gpu *gpu, uint64_t *value)
{
	*value = gpu_read64(gpu, REG_A5XX_RBBM_PERFCTR_CP_0_LO,
		REG_A5XX_RBBM_PERFCTR_CP_0_HI);

	return 0;
}