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
struct __vxge_hw_channel {size_t reserve_ptr; scalar_t__ reserve_top; scalar_t__ length; scalar_t__ free_ptr; TYPE_1__* stats; int /*<<< orphan*/  free_arr; void** reserve_arr; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_2__ {int /*<<< orphan*/  full_cnt; int /*<<< orphan*/  reserve_free_swaps_cnt; } ;

/* Variables and functions */
 int VXGE_HW_INF_OUT_OF_DESCRIPTORS ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  swap (void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum vxge_hw_status
vxge_hw_channel_dtr_alloc(struct __vxge_hw_channel *channel, void **dtrh)
{
	if (channel->reserve_ptr - channel->reserve_top > 0) {
_alloc_after_swap:
		*dtrh =	channel->reserve_arr[--channel->reserve_ptr];

		return VXGE_HW_OK;
	}

	/* switch between empty	and full arrays	*/

	/* the idea behind such	a design is that by having free	and reserved
	 * arrays separated we basically separated irq and non-irq parts.
	 * i.e.	no additional lock need	to be done when	we free	a resource */

	if (channel->length - channel->free_ptr > 0) {
		swap(channel->reserve_arr, channel->free_arr);
		channel->reserve_ptr = channel->length;
		channel->reserve_top = channel->free_ptr;
		channel->free_ptr = channel->length;

		channel->stats->reserve_free_swaps_cnt++;

		goto _alloc_after_swap;
	}

	channel->stats->full_cnt++;

	*dtrh =	NULL;
	return VXGE_HW_INF_OUT_OF_DESCRIPTORS;
}