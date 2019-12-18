#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct host1x_job {TYPE_3__* channel; int /*<<< orphan*/  syncpt_id; scalar_t__ timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  pos; } ;
struct TYPE_4__ {int /*<<< orphan*/  initialized; } ;
struct host1x_cdma {TYPE_2__ push_buffer; int /*<<< orphan*/  first_get; scalar_t__ slots_used; scalar_t__ slots_free; int /*<<< orphan*/  running; int /*<<< orphan*/  lock; TYPE_1__ timeout; } ;
struct host1x {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_cdma_start (struct host1x*,struct host1x_cdma*) ; 
 int host1x_hw_cdma_timeout_init (struct host1x*,struct host1x_cdma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_host1x_cdma_begin (int /*<<< orphan*/ ) ; 

int host1x_cdma_begin(struct host1x_cdma *cdma, struct host1x_job *job)
{
	struct host1x *host1x = cdma_to_host1x(cdma);

	mutex_lock(&cdma->lock);

	if (job->timeout) {
		/* init state on first submit with timeout value */
		if (!cdma->timeout.initialized) {
			int err;

			err = host1x_hw_cdma_timeout_init(host1x, cdma,
							  job->syncpt_id);
			if (err) {
				mutex_unlock(&cdma->lock);
				return err;
			}
		}
	}

	if (!cdma->running)
		host1x_hw_cdma_start(host1x, cdma);

	cdma->slots_free = 0;
	cdma->slots_used = 0;
	cdma->first_get = cdma->push_buffer.pos;

	trace_host1x_cdma_begin(dev_name(job->channel->dev));
	return 0;
}