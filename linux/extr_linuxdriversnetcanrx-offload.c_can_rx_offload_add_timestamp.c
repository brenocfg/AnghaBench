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
struct net_device {int dummy; } ;
struct can_rx_offload {scalar_t__ mb_first; scalar_t__ mb_last; int inc; int /*<<< orphan*/  mailbox_read; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_LONG_LONG ; 
 int EINVAL ; 
 int can_rx_offload_init_queue (struct net_device*,struct can_rx_offload*,unsigned int) ; 

int can_rx_offload_add_timestamp(struct net_device *dev, struct can_rx_offload *offload)
{
	unsigned int weight;

	if (offload->mb_first > BITS_PER_LONG_LONG ||
	    offload->mb_last > BITS_PER_LONG_LONG || !offload->mailbox_read)
		return -EINVAL;

	if (offload->mb_first < offload->mb_last) {
		offload->inc = true;
		weight = offload->mb_last - offload->mb_first;
	} else {
		offload->inc = false;
		weight = offload->mb_first - offload->mb_last;
	}

	return can_rx_offload_init_queue(dev, offload, weight);
}