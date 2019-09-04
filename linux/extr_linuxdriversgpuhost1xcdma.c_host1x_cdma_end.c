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
struct host1x_job {TYPE_1__* channel; scalar_t__ timeout; int /*<<< orphan*/  list; int /*<<< orphan*/  num_slots; int /*<<< orphan*/  first_get; } ;
struct host1x_cdma {int /*<<< orphan*/  lock; int /*<<< orphan*/  sync_queue; int /*<<< orphan*/  slots_used; int /*<<< orphan*/  first_get; } ;
struct host1x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdma_start_timer_locked (struct host1x_cdma*,struct host1x_job*) ; 
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_cdma_flush (struct host1x*,struct host1x_cdma*) ; 
 int /*<<< orphan*/  host1x_job_get (struct host1x_job*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_host1x_cdma_end (int /*<<< orphan*/ ) ; 

void host1x_cdma_end(struct host1x_cdma *cdma,
		     struct host1x_job *job)
{
	struct host1x *host1x = cdma_to_host1x(cdma);
	bool idle = list_empty(&cdma->sync_queue);

	host1x_hw_cdma_flush(host1x, cdma);

	job->first_get = cdma->first_get;
	job->num_slots = cdma->slots_used;
	host1x_job_get(job);
	list_add_tail(&job->list, &cdma->sync_queue);

	/* start timer on idle -> active transitions */
	if (job->timeout && idle)
		cdma_start_timer_locked(cdma, job);

	trace_host1x_cdma_end(dev_name(job->channel->dev));
	mutex_unlock(&cdma->lock);
}