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
struct host1x_cdma {scalar_t__ event; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; struct push_buffer push_buffer; } ;
struct host1x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CDMA_EVENT_NONE ; 
 scalar_t__ CDMA_EVENT_PUSH_BUFFER_SPACE ; 
 TYPE_1__* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_cdma_flush (struct host1x*,struct host1x_cdma*) ; 
 unsigned int host1x_pushbuffer_space (struct push_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  trace_host1x_wait_cdma (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int host1x_cdma_wait_pushbuffer_space(struct host1x *host1x,
				      struct host1x_cdma *cdma,
				      unsigned int needed)
{
	while (true) {
		struct push_buffer *pb = &cdma->push_buffer;
		unsigned int space;

		space = host1x_pushbuffer_space(pb);
		if (space >= needed)
			break;

		trace_host1x_wait_cdma(dev_name(cdma_to_channel(cdma)->dev),
				       CDMA_EVENT_PUSH_BUFFER_SPACE);

		host1x_hw_cdma_flush(host1x, cdma);

		/* If somebody has managed to already start waiting, yield */
		if (cdma->event != CDMA_EVENT_NONE) {
			mutex_unlock(&cdma->lock);
			schedule();
			mutex_lock(&cdma->lock);
			continue;
		}

		cdma->event = CDMA_EVENT_PUSH_BUFFER_SPACE;

		mutex_unlock(&cdma->lock);
		wait_for_completion(&cdma->complete);
		mutex_lock(&cdma->lock);
	}

	return 0;
}