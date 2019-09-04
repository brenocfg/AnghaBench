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
struct kfd_dev {TYPE_1__* device_info; int /*<<< orphan*/  ih_fifo; } ;
struct TYPE_2__ {int ih_ring_entry_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfd_chardev () ; 
 int kfifo_in (int /*<<< orphan*/ *,void const*,int) ; 

bool enqueue_ih_ring_entry(struct kfd_dev *kfd,	const void *ih_ring_entry)
{
	int count;

	count = kfifo_in(&kfd->ih_fifo, ih_ring_entry,
				kfd->device_info->ih_ring_entry_size);
	if (count != kfd->device_info->ih_ring_entry_size) {
		dev_err_ratelimited(kfd_chardev(),
			"Interrupt ring overflow, dropping interrupt %d\n",
			count);
		return false;
	}

	return true;
}