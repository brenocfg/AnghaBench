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
struct devfreq {TYPE_1__* profile; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {scalar_t__ polling_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfreq_monitor ; 
 int /*<<< orphan*/  devfreq_wq ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void devfreq_monitor_start(struct devfreq *devfreq)
{
	INIT_DEFERRABLE_WORK(&devfreq->work, devfreq_monitor);
	if (devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jiffies(devfreq->profile->polling_ms));
}