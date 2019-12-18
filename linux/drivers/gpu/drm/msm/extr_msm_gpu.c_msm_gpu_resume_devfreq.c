#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  devfreq; int /*<<< orphan*/  time; scalar_t__ busy_cycles; } ;
struct msm_gpu {TYPE_1__ devfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfreq_resume_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

void msm_gpu_resume_devfreq(struct msm_gpu *gpu)
{
	gpu->devfreq.busy_cycles = 0;
	gpu->devfreq.time = ktime_get();

	devfreq_resume_device(gpu->devfreq.devfreq);
}