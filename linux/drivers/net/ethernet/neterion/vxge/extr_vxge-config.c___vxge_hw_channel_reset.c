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
typedef  size_t u32 ;
struct __vxge_hw_channel {size_t length; size_t free_ptr; size_t reserve_ptr; scalar_t__ compl_index; scalar_t__ post_index; scalar_t__ reserve_top; int /*<<< orphan*/ ** work_arr; int /*<<< orphan*/ ** free_arr; int /*<<< orphan*/ * orig_arr; int /*<<< orphan*/ * reserve_arr; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int VXGE_HW_OK ; 

__attribute__((used)) static enum vxge_hw_status
__vxge_hw_channel_reset(struct __vxge_hw_channel *channel)
{
	u32 i;

	for (i = 0; i < channel->length; i++) {
		if (channel->reserve_arr != NULL)
			channel->reserve_arr[i] = channel->orig_arr[i];
		if (channel->free_arr != NULL)
			channel->free_arr[i] = NULL;
		if (channel->work_arr != NULL)
			channel->work_arr[i] = NULL;
	}
	channel->free_ptr = channel->length;
	channel->reserve_ptr = channel->length;
	channel->reserve_top = 0;
	channel->post_index = 0;
	channel->compl_index = 0;

	return VXGE_HW_OK;
}