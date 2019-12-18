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
struct TYPE_4__ {TYPE_1__* slot; } ;
struct panfrost_device {int /*<<< orphan*/  dev; TYPE_2__ devfreq; int /*<<< orphan*/  clock; } ;
struct device {int dummy; } ;
struct devfreq_dev_status {int current_frequency; int total_time; int busy_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  busy_time; int /*<<< orphan*/  idle_time; } ;

/* Variables and functions */
 int NUM_JOB_SLOTS ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panfrost_devfreq_reset (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_devfreq_update_utilization (struct panfrost_device*,int) ; 
 struct panfrost_device* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int panfrost_devfreq_get_dev_status(struct device *dev,
					   struct devfreq_dev_status *status)
{
	struct panfrost_device *pfdev = platform_get_drvdata(to_platform_device(dev));
	int i;

	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		panfrost_devfreq_update_utilization(pfdev, i);
	}

	status->current_frequency = clk_get_rate(pfdev->clock);
	status->total_time = ktime_to_ns(ktime_add(pfdev->devfreq.slot[0].busy_time,
						   pfdev->devfreq.slot[0].idle_time));

	status->busy_time = 0;
	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		status->busy_time += ktime_to_ns(pfdev->devfreq.slot[i].busy_time);
	}

	/* We're scheduling only to one core atm, so don't divide for now */
	/* status->busy_time /= NUM_JOB_SLOTS; */

	panfrost_devfreq_reset(pfdev);

	dev_dbg(pfdev->dev, "busy %lu total %lu %lu %% freq %lu MHz\n", status->busy_time,
		status->total_time,
		status->busy_time / (status->total_time / 100),
		status->current_frequency / 1000 / 1000);

	return 0;
}