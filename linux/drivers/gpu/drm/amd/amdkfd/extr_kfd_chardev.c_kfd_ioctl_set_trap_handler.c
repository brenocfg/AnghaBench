#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kfd_process_device {int /*<<< orphan*/  qpd; } ;
struct kfd_process {int /*<<< orphan*/  mutex; } ;
struct kfd_ioctl_set_trap_handler_args {int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; int /*<<< orphan*/  gpu_id; } ;
struct kfd_dev {TYPE_2__* dqm; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* set_trap_handler ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ IS_ERR (struct kfd_process_device*) ; 
 struct kfd_process_device* kfd_bind_process_to_device (struct kfd_dev*,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kfd_ioctl_set_trap_handler(struct file *filep,
					struct kfd_process *p, void *data)
{
	struct kfd_ioctl_set_trap_handler_args *args = data;
	struct kfd_dev *dev;
	int err = 0;
	struct kfd_process_device *pdd;

	dev = kfd_device_by_id(args->gpu_id);
	if (!dev)
		return -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		err = -ESRCH;
		goto out;
	}

	if (dev->dqm->ops.set_trap_handler(dev->dqm,
					&pdd->qpd,
					args->tba_addr,
					args->tma_addr))
		err = -EINVAL;

out:
	mutex_unlock(&p->mutex);

	return err;
}