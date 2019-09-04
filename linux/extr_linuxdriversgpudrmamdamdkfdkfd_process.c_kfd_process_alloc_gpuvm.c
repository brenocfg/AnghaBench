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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_mem {int dummy; } ;
struct kfd_process_device {int /*<<< orphan*/  vm; struct kfd_dev* dev; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_2__ {int (* alloc_memory_of_gpu ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kgd_mem**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int (* map_memory_to_gpu ) (int /*<<< orphan*/ ,struct kgd_mem*,int /*<<< orphan*/ ) ;int (* sync_memory ) (int /*<<< orphan*/ ,struct kgd_mem*,int) ;int (* map_gtt_bo_to_kernel ) (int /*<<< orphan*/ ,struct kgd_mem*,void**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* free_memory_of_gpu ) (int /*<<< orphan*/ ,struct kgd_mem*) ;} ;

/* Variables and functions */
 int kfd_process_device_create_obj_handle (struct kfd_process_device*,struct kgd_mem*) ; 
 int /*<<< orphan*/  kfd_process_device_remove_obj_handle (struct kfd_process_device*,int) ; 
 int /*<<< orphan*/  kfd_process_free_gpuvm (struct kgd_mem*,struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kgd_mem**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,struct kgd_mem*,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,struct kgd_mem*,int) ; 
 int stub4 (int /*<<< orphan*/ ,struct kgd_mem*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,struct kgd_mem*) ; 

__attribute__((used)) static int kfd_process_alloc_gpuvm(struct kfd_process_device *pdd,
				   uint64_t gpu_va, uint32_t size,
				   uint32_t flags, void **kptr)
{
	struct kfd_dev *kdev = pdd->dev;
	struct kgd_mem *mem = NULL;
	int handle;
	int err;

	err = kdev->kfd2kgd->alloc_memory_of_gpu(kdev->kgd, gpu_va, size,
						 pdd->vm, &mem, NULL, flags);
	if (err)
		goto err_alloc_mem;

	err = kdev->kfd2kgd->map_memory_to_gpu(kdev->kgd, mem, pdd->vm);
	if (err)
		goto err_map_mem;

	err = kdev->kfd2kgd->sync_memory(kdev->kgd, mem, true);
	if (err) {
		pr_debug("Sync memory failed, wait interrupted by user signal\n");
		goto sync_memory_failed;
	}

	/* Create an obj handle so kfd_process_device_remove_obj_handle
	 * will take care of the bo removal when the process finishes.
	 * We do not need to take p->mutex, because the process is just
	 * created and the ioctls have not had the chance to run.
	 */
	handle = kfd_process_device_create_obj_handle(pdd, mem);

	if (handle < 0) {
		err = handle;
		goto free_gpuvm;
	}

	if (kptr) {
		err = kdev->kfd2kgd->map_gtt_bo_to_kernel(kdev->kgd,
				(struct kgd_mem *)mem, kptr, NULL);
		if (err) {
			pr_debug("Map GTT BO to kernel failed\n");
			goto free_obj_handle;
		}
	}

	return err;

free_obj_handle:
	kfd_process_device_remove_obj_handle(pdd, handle);
free_gpuvm:
sync_memory_failed:
	kfd_process_free_gpuvm(mem, pdd);
	return err;

err_map_mem:
	kdev->kfd2kgd->free_memory_of_gpu(kdev->kgd, mem);
err_alloc_mem:
	*kptr = NULL;
	return err;
}