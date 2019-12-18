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
struct kfd_process {int dummy; } ;
struct kfd_ioctl_dbg_unregister_args {int /*<<< orphan*/  gpu_id; } ;
struct kfd_dev {int /*<<< orphan*/ * dbgmgr; TYPE_1__* device_info; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ asic_family; } ;

/* Variables and functions */
 scalar_t__ CHIP_CARRIZO ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfd_dbgmgr_destroy (int /*<<< orphan*/ *) ; 
 long kfd_dbgmgr_unregister (int /*<<< orphan*/ *,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_get_dbgmgr_mutex () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int kfd_ioctl_dbg_unregister(struct file *filep,
				struct kfd_process *p, void *data)
{
	struct kfd_ioctl_dbg_unregister_args *args = data;
	struct kfd_dev *dev;
	long status;

	dev = kfd_device_by_id(args->gpu_id);
	if (!dev || !dev->dbgmgr)
		return -EINVAL;

	if (dev->device_info->asic_family == CHIP_CARRIZO) {
		pr_debug("kfd_ioctl_dbg_unregister not supported on CZ\n");
		return -EINVAL;
	}

	mutex_lock(kfd_get_dbgmgr_mutex());

	status = kfd_dbgmgr_unregister(dev->dbgmgr, p);
	if (!status) {
		kfd_dbgmgr_destroy(dev->dbgmgr);
		dev->dbgmgr = NULL;
	}

	mutex_unlock(kfd_get_dbgmgr_mutex());

	return status;
}