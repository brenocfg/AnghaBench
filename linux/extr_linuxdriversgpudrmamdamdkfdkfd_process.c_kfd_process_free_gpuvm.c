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
struct kgd_mem {int dummy; } ;
struct kfd_process_device {int /*<<< orphan*/  vm; struct kfd_dev* dev; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_memory_of_gpu ) (int /*<<< orphan*/ ,struct kgd_mem*) ;int /*<<< orphan*/  (* unmap_memory_to_gpu ) (int /*<<< orphan*/ ,struct kgd_mem*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kgd_mem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct kgd_mem*) ; 

__attribute__((used)) static void kfd_process_free_gpuvm(struct kgd_mem *mem,
			struct kfd_process_device *pdd)
{
	struct kfd_dev *dev = pdd->dev;

	dev->kfd2kgd->unmap_memory_to_gpu(dev->kgd, mem, pdd->vm);
	dev->kfd2kgd->free_memory_of_gpu(dev->kgd, mem);
}