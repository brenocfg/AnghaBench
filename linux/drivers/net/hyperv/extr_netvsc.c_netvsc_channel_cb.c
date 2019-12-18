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
struct hv_ring_buffer_info {scalar_t__ priv_read_index; } ;
struct vmbus_channel {struct hv_ring_buffer_info inbound; } ;
struct netvsc_channel {int /*<<< orphan*/  napi; struct vmbus_channel* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_begin_read (struct hv_ring_buffer_info*) ; 
 scalar_t__ hv_get_ring_buffer (struct hv_ring_buffer_info*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (scalar_t__) ; 

void netvsc_channel_cb(void *context)
{
	struct netvsc_channel *nvchan = context;
	struct vmbus_channel *channel = nvchan->channel;
	struct hv_ring_buffer_info *rbi = &channel->inbound;

	/* preload first vmpacket descriptor */
	prefetch(hv_get_ring_buffer(rbi) + rbi->priv_read_index);

	if (napi_schedule_prep(&nvchan->napi)) {
		/* disable interrupts from host */
		hv_begin_read(rbi);

		__napi_schedule_irqoff(&nvchan->napi);
	}
}