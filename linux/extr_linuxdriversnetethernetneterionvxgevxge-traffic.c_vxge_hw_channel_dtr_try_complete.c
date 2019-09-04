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
struct __vxge_hw_channel {size_t compl_index; size_t length; void** work_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  vxge_assert (int) ; 

void
vxge_hw_channel_dtr_try_complete(struct __vxge_hw_channel *channel, void **dtrh)
{
	vxge_assert(channel->compl_index < channel->length);

	*dtrh =	channel->work_arr[channel->compl_index];
	prefetch(*dtrh);
}