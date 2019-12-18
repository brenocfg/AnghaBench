#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * devfreq; } ;
struct msm_gpu {TYPE_3__ devfreq; TYPE_1__* pdev; int /*<<< orphan*/  fast_rate; TYPE_2__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  initial_freq; } ;
struct TYPE_7__ {int /*<<< orphan*/  gpu_busy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_SIMPLE_ONDEMAND ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfreq_suspend_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_devfreq_add_device (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__ msm_devfreq_profile ; 

__attribute__((used)) static void msm_devfreq_init(struct msm_gpu *gpu)
{
	/* We need target support to do devfreq */
	if (!gpu->funcs->gpu_busy)
		return;

	msm_devfreq_profile.initial_freq = gpu->fast_rate;

	/*
	 * Don't set the freq_table or max_state and let devfreq build the table
	 * from OPP
	 */

	gpu->devfreq.devfreq = devm_devfreq_add_device(&gpu->pdev->dev,
			&msm_devfreq_profile, DEVFREQ_GOV_SIMPLE_ONDEMAND,
			NULL);

	if (IS_ERR(gpu->devfreq.devfreq)) {
		DRM_DEV_ERROR(&gpu->pdev->dev, "Couldn't initialize GPU devfreq\n");
		gpu->devfreq.devfreq = NULL;
	}

	devfreq_suspend_device(gpu->devfreq.devfreq);
}