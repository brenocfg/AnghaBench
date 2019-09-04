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
 int a5xx_gpmu_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_lm_enable (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_lm_setup (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_pc_init (struct msm_gpu*) ; 

int a5xx_power_init(struct msm_gpu *gpu)
{
	int ret;

	/* Set up the limits management */
	a5xx_lm_setup(gpu);

	/* Set up SP/TP power collpase */
	a5xx_pc_init(gpu);

	/* Start the GPMU */
	ret = a5xx_gpmu_init(gpu);
	if (ret)
		return ret;

	/* Start the limits management */
	a5xx_lm_enable(gpu);

	return 0;
}