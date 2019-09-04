#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vmid; int /*<<< orphan*/  sh_hidden_private_base; } ;
struct kfd_process_device {TYPE_3__ qpd; } ;
struct kfd_process {int /*<<< orphan*/  mutex; } ;
struct kfd_ioctl_set_scratch_backing_va_args {int /*<<< orphan*/  va_addr; int /*<<< orphan*/  gpu_id; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_2__* kfd2kgd; TYPE_1__* dqm; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_scratch_backing_va ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_4__ {scalar_t__ sched_policy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct kfd_process_device*) ; 
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 long PTR_ERR (struct kfd_process_device*) ; 
 struct kfd_process_device* kfd_bind_process_to_device (struct kfd_dev*,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int kfd_ioctl_set_scratch_backing_va(struct file *filep,
					struct kfd_process *p, void *data)
{
	struct kfd_ioctl_set_scratch_backing_va_args *args = data;
	struct kfd_process_device *pdd;
	struct kfd_dev *dev;
	long err;

	dev = kfd_device_by_id(args->gpu_id);
	if (!dev)
		return -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		err = PTR_ERR(pdd);
		goto bind_process_to_device_fail;
	}

	pdd->qpd.sh_hidden_private_base = args->va_addr;

	mutex_unlock(&p->mutex);

	if (dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS &&
	    pdd->qpd.vmid != 0)
		dev->kfd2kgd->set_scratch_backing_va(
			dev->kgd, args->va_addr, pdd->qpd.vmid);

	return 0;

bind_process_to_device_fail:
	mutex_unlock(&p->mutex);
	return err;
}