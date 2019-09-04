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
struct kfd_dev {int interrupts_active; int /*<<< orphan*/  interrupt_work; int /*<<< orphan*/  interrupt_lock; int /*<<< orphan*/  ih_wq; TYPE_1__* device_info; int /*<<< orphan*/  ih_fifo; } ;
struct TYPE_2__ {int ih_ring_entry_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int KFD_IH_NUM_ENTRIES ; 
 int /*<<< orphan*/  WQ_HIGHPRI ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  interrupt_wq ; 
 int /*<<< orphan*/  kfd_chardev () ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int kfd_interrupt_init(struct kfd_dev *kfd)
{
	int r;

	r = kfifo_alloc(&kfd->ih_fifo,
		KFD_IH_NUM_ENTRIES * kfd->device_info->ih_ring_entry_size,
		GFP_KERNEL);
	if (r) {
		dev_err(kfd_chardev(), "Failed to allocate IH fifo\n");
		return r;
	}

	kfd->ih_wq = alloc_workqueue("KFD IH", WQ_HIGHPRI, 1);
	spin_lock_init(&kfd->interrupt_lock);

	INIT_WORK(&kfd->interrupt_work, interrupt_wq);

	kfd->interrupts_active = true;

	/*
	 * After this function returns, the interrupt will be enabled. This
	 * barrier ensures that the interrupt running on a different processor
	 * sees all the above writes.
	 */
	smp_wmb();

	return 0;
}