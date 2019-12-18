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
struct __vxge_hw_channel {size_t compl_index; size_t length; TYPE_1__* stats; int /*<<< orphan*/ ** work_arr; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_compl_cnt; } ;

/* Variables and functions */

void vxge_hw_channel_dtr_complete(struct __vxge_hw_channel *channel)
{
	channel->work_arr[channel->compl_index]	= NULL;

	/* wrap-around */
	if (++channel->compl_index == channel->length)
		channel->compl_index = 0;

	channel->stats->total_compl_cnt++;
}