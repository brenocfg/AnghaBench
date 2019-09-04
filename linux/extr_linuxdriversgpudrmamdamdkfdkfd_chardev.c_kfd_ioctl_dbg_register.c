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
struct kfd_process_device {int dummy; } ;
struct kfd_process {int /*<<< orphan*/  mutex; } ;
struct kfd_ioctl_dbg_register_args {int /*<<< orphan*/  gpu_id; } ;
struct kfd_dev {struct kfd_dbgmgr* dbgmgr; TYPE_1__* device_info; } ;
struct kfd_dbgmgr {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ asic_family; } ;

/* Variables and functions */
 scalar_t__ CHIP_CARRIZO ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct kfd_process_device*) ; 
 long PTR_ERR (struct kfd_process_device*) ; 
 struct kfd_process_device* kfd_bind_process_to_device (struct kfd_dev*,struct kfd_process*) ; 
 int kfd_dbgmgr_create (struct kfd_dbgmgr**,struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_dbgmgr_destroy (struct kfd_dbgmgr*) ; 
 long kfd_dbgmgr_register (struct kfd_dbgmgr*,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kfd_get_dbgmgr_mutex () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int kfd_ioctl_dbg_register(struct file *filep,
				struct kfd_process *p, void *data)
{
	struct kfd_ioctl_dbg_register_args *args = data;
	struct kfd_dev *dev;
	struct kfd_dbgmgr *dbgmgr_ptr;
	struct kfd_process_device *pdd;
	bool create_ok;
	long status = 0;

	dev = kfd_device_by_id(args->gpu_id);
	if (!dev)
		return -EINVAL;

	if (dev->device_info->asic_family == CHIP_CARRIZO) {
		pr_debug("kfd_ioctl_dbg_register not supported on CZ\n");
		return -EINVAL;
	}

	mutex_lock(&p->mutex);
	mutex_lock(kfd_get_dbgmgr_mutex());

	/*
	 * make sure that we have pdd, if this the first queue created for
	 * this process
	 */
	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		status = PTR_ERR(pdd);
		goto out;
	}

	if (!dev->dbgmgr) {
		/* In case of a legal call, we have no dbgmgr yet */
		create_ok = kfd_dbgmgr_create(&dbgmgr_ptr, dev);
		if (create_ok) {
			status = kfd_dbgmgr_register(dbgmgr_ptr, p);
			if (status != 0)
				kfd_dbgmgr_destroy(dbgmgr_ptr);
			else
				dev->dbgmgr = dbgmgr_ptr;
		}
	} else {
		pr_debug("debugger already registered\n");
		status = -EINVAL;
	}

out:
	mutex_unlock(kfd_get_dbgmgr_mutex());
	mutex_unlock(&p->mutex);

	return status;
}