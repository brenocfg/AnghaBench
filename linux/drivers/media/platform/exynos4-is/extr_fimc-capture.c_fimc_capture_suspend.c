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
struct TYPE_2__ {int /*<<< orphan*/  ve; } ;
struct fimc_dev {TYPE_1__ vid_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  close ; 
 int fimc_capture_busy (struct fimc_dev*) ; 
 int fimc_pipeline_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fimc_stop_capture (struct fimc_dev*,int) ; 

int fimc_capture_suspend(struct fimc_dev *fimc)
{
	bool suspend = fimc_capture_busy(fimc);

	int ret = fimc_stop_capture(fimc, suspend);
	if (ret)
		return ret;
	return fimc_pipeline_call(&fimc->vid_cap.ve, close);
}