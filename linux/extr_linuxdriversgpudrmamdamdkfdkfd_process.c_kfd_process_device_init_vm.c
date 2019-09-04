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
struct kfd_process_device {int /*<<< orphan*/ * vm; struct file* drm_file; struct kfd_dev* dev; struct kfd_process* process; } ;
struct kfd_process {int /*<<< orphan*/  ef; int /*<<< orphan*/  kgd_process_info; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* acquire_process_vm ) (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* create_process_vm ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* destroy_process_vm ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfd_process_device_free_bos (struct kfd_process_device*) ; 
 int kfd_process_device_init_cwsr_dgpu (struct kfd_process_device*) ; 
 int kfd_process_device_reserve_ib_mem (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int kfd_process_device_init_vm(struct kfd_process_device *pdd,
			       struct file *drm_file)
{
	struct kfd_process *p;
	struct kfd_dev *dev;
	int ret;

	if (pdd->vm)
		return drm_file ? -EBUSY : 0;

	p = pdd->process;
	dev = pdd->dev;

	if (drm_file)
		ret = dev->kfd2kgd->acquire_process_vm(
			dev->kgd, drm_file,
			&pdd->vm, &p->kgd_process_info, &p->ef);
	else
		ret = dev->kfd2kgd->create_process_vm(
			dev->kgd, &pdd->vm, &p->kgd_process_info, &p->ef);
	if (ret) {
		pr_err("Failed to create process VM object\n");
		return ret;
	}

	ret = kfd_process_device_reserve_ib_mem(pdd);
	if (ret)
		goto err_reserve_ib_mem;
	ret = kfd_process_device_init_cwsr_dgpu(pdd);
	if (ret)
		goto err_init_cwsr;

	pdd->drm_file = drm_file;

	return 0;

err_init_cwsr:
err_reserve_ib_mem:
	kfd_process_device_free_bos(pdd);
	if (!drm_file)
		dev->kfd2kgd->destroy_process_vm(dev->kgd, pdd->vm);
	pdd->vm = NULL;

	return ret;
}