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
struct kfd_dev {int dummy; } ;
struct kernel_queue {int /*<<< orphan*/  eop_kernel_addr; TYPE_1__* eop_mem; int /*<<< orphan*/  eop_gpu_addr; } ;
typedef  enum kfd_queue_type { ____Placeholder_kfd_queue_type } kfd_queue_type ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_ptr; int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int kfd_gtt_sa_allocate (struct kfd_dev*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool initialize_vi(struct kernel_queue *kq, struct kfd_dev *dev,
			enum kfd_queue_type type, unsigned int queue_size)
{
	int retval;

	retval = kfd_gtt_sa_allocate(dev, PAGE_SIZE, &kq->eop_mem);
	if (retval != 0)
		return false;

	kq->eop_gpu_addr = kq->eop_mem->gpu_addr;
	kq->eop_kernel_addr = kq->eop_mem->cpu_ptr;

	memset(kq->eop_kernel_addr, 0, PAGE_SIZE);

	return true;
}