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
struct msm_gem_submit {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void msm_gpu_crashstate_capture(struct msm_gpu *gpu,
		struct msm_gem_submit *submit, char *comm, char *cmd)
{
}