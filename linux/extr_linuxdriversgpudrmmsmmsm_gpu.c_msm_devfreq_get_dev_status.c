#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  time; scalar_t__ busy_cycles; } ;
struct msm_gpu {TYPE_2__ devfreq; TYPE_1__* funcs; int /*<<< orphan*/  core_clk; } ;
struct device {int dummy; } ;
struct devfreq_dev_status {unsigned long current_frequency; int busy_time; int /*<<< orphan*/  total_time; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* gpu_busy ) (struct msm_gpu*,scalar_t__*) ;} ;

/* Variables and functions */
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_gpu* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,scalar_t__*) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int msm_devfreq_get_dev_status(struct device *dev,
		struct devfreq_dev_status *status)
{
	struct msm_gpu *gpu = platform_get_drvdata(to_platform_device(dev));
	u64 cycles;
	u32 freq = ((u32) status->current_frequency) / 1000000;
	ktime_t time;

	status->current_frequency = (unsigned long) clk_get_rate(gpu->core_clk);
	gpu->funcs->gpu_busy(gpu, &cycles);

	status->busy_time = ((u32) (cycles - gpu->devfreq.busy_cycles)) / freq;

	gpu->devfreq.busy_cycles = cycles;

	time = ktime_get();
	status->total_time = ktime_us_delta(time, gpu->devfreq.time);
	gpu->devfreq.time = time;

	return 0;
}