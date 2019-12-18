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
struct push_buffer {int dummy; } ;
struct host1x_cdma {int event; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  sync_queue; struct push_buffer push_buffer; } ;
typedef  enum cdma_event { ____Placeholder_cdma_event } cdma_event ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CDMA_EVENT_NONE ; 
#define  CDMA_EVENT_PUSH_BUFFER_SPACE 129 
#define  CDMA_EVENT_SYNC_QUEUE_EMPTY 128 
 unsigned int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 unsigned int host1x_pushbuffer_space (struct push_buffer*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  trace_host1x_wait_cdma (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

unsigned int host1x_cdma_wait_locked(struct host1x_cdma *cdma,
				     enum cdma_event event)
{
	for (;;) {
		struct push_buffer *pb = &cdma->push_buffer;
		unsigned int space;

		switch (event) {
		case CDMA_EVENT_SYNC_QUEUE_EMPTY:
			space = list_empty(&cdma->sync_queue) ? 1 : 0;
			break;

		case CDMA_EVENT_PUSH_BUFFER_SPACE:
			space = host1x_pushbuffer_space(pb);
			break;

		default:
			WARN_ON(1);
			return -EINVAL;
		}

		if (space)
			return space;

		trace_host1x_wait_cdma(dev_name(cdma_to_channel(cdma)->dev),
				       event);

		/* If somebody has managed to already start waiting, yield */
		if (cdma->event != CDMA_EVENT_NONE) {
			mutex_unlock(&cdma->lock);
			schedule();
			mutex_lock(&cdma->lock);
			continue;
		}

		cdma->event = event;

		mutex_unlock(&cdma->lock);
		wait_for_completion(&cdma->complete);
		mutex_lock(&cdma->lock);
	}

	return 0;
}