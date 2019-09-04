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
struct kfd_dev {int /*<<< orphan*/  gtt_mem; int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; int /*<<< orphan*/  dqm; scalar_t__ init_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_gtt_mem ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_queue_manager_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_doorbell_fini (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_gtt_sa_fini (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_interrupt_exit (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_topology_remove_device (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfree (struct kfd_dev*) ; 
 int /*<<< orphan*/  kgd2kfd_suspend (struct kfd_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kgd2kfd_device_exit(struct kfd_dev *kfd)
{
	if (kfd->init_complete) {
		kgd2kfd_suspend(kfd);
		device_queue_manager_uninit(kfd->dqm);
		kfd_interrupt_exit(kfd);
		kfd_topology_remove_device(kfd);
		kfd_doorbell_fini(kfd);
		kfd_gtt_sa_fini(kfd);
		kfd->kfd2kgd->free_gtt_mem(kfd->kgd, kfd->gtt_mem);
	}

	kfree(kfd);
}