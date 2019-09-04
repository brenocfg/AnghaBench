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
struct msm_gpu {scalar_t__ gpu_reg; scalar_t__ gpu_cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static int disable_pwrrail(struct msm_gpu *gpu)
{
	if (gpu->gpu_cx)
		regulator_disable(gpu->gpu_cx);
	if (gpu->gpu_reg)
		regulator_disable(gpu->gpu_reg);
	return 0;
}