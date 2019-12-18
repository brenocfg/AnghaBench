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
typedef  size_t u16 ;
struct dln2_dev {TYPE_1__* mod_rx_slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_free_slot (struct dln2_dev*,size_t,int*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_rx_slot(struct dln2_dev *dln2, u16 handle)
{
	int ret;
	int slot;

	/*
	 * No need to timeout here, the wait is bounded by the timeout in
	 * _dln2_transfer.
	 */
	ret = wait_event_interruptible(dln2->mod_rx_slots[handle].wq,
				       find_free_slot(dln2, handle, &slot));
	if (ret < 0)
		return ret;

	return slot;
}