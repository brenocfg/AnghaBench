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
struct dma_chan {int client_count; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ privatecnt; int /*<<< orphan*/  cap_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  dma_cap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_put (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dma_release_channel(struct dma_chan *chan)
{
	mutex_lock(&dma_list_mutex);
	WARN_ONCE(chan->client_count != 1,
		  "chan reference count %d != 1\n", chan->client_count);
	dma_chan_put(chan);
	/* drop PRIVATE cap enabled by __dma_request_channel() */
	if (--chan->device->privatecnt == 0)
		dma_cap_clear(DMA_PRIVATE, chan->device->cap_mask);
	mutex_unlock(&dma_list_mutex);
}