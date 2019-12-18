#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmbus_channel {int ringbuffer_pagecount; int /*<<< orphan*/ * ringbuffer_page; int /*<<< orphan*/  inbound; int /*<<< orphan*/  outbound; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  hv_ringbuffer_cleanup (int /*<<< orphan*/ *) ; 

void vmbus_free_ring(struct vmbus_channel *channel)
{
	hv_ringbuffer_cleanup(&channel->outbound);
	hv_ringbuffer_cleanup(&channel->inbound);

	if (channel->ringbuffer_page) {
		__free_pages(channel->ringbuffer_page,
			     get_order(channel->ringbuffer_pagecount
				       << PAGE_SHIFT));
		channel->ringbuffer_page = NULL;
	}
}