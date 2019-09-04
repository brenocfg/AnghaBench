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
struct __vxge_hw_channel {size_t post_index; size_t length; int /*<<< orphan*/ ** work_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vxge_hw_channel_dtr_post(struct __vxge_hw_channel *channel, void *dtrh)
{
	vxge_assert(channel->work_arr[channel->post_index] == NULL);

	channel->work_arr[channel->post_index++] = dtrh;

	/* wrap-around */
	if (channel->post_index	== channel->length)
		channel->post_index = 0;
}