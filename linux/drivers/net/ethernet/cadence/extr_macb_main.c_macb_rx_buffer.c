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
struct macb_queue {void* rx_buffers; TYPE_1__* bp; } ;
struct TYPE_2__ {int rx_buffer_size; } ;

/* Variables and functions */
 int macb_rx_ring_wrap (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void *macb_rx_buffer(struct macb_queue *queue, unsigned int index)
{
	return queue->rx_buffers + queue->bp->rx_buffer_size *
	       macb_rx_ring_wrap(queue->bp, index);
}