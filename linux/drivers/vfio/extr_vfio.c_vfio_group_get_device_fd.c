#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfio_group {scalar_t__ noiommu; int /*<<< orphan*/  container_users; TYPE_1__* container; } ;
struct vfio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  device_data; TYPE_2__* ops; } ;
struct file {int f_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  comm; } ;
struct TYPE_6__ {int (* open ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  iommu_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int FMODE_LSEEK ; 
 int FMODE_PREAD ; 
 int FMODE_PWRITE ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PTR_ERR (struct file*) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct vfio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  vfio_device_fops ; 
 struct vfio_device* vfio_device_get_from_name (struct vfio_group*,char*) ; 
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 
 int /*<<< orphan*/  vfio_group_viable (struct vfio_group*) ; 

__attribute__((used)) static int vfio_group_get_device_fd(struct vfio_group *group, char *buf)
{
	struct vfio_device *device;
	struct file *filep;
	int ret;

	if (0 == atomic_read(&group->container_users) ||
	    !group->container->iommu_driver || !vfio_group_viable(group))
		return -EINVAL;

	if (group->noiommu && !capable(CAP_SYS_RAWIO))
		return -EPERM;

	device = vfio_device_get_from_name(group, buf);
	if (!device)
		return -ENODEV;

	ret = device->ops->open(device->device_data);
	if (ret) {
		vfio_device_put(device);
		return ret;
	}

	/*
	 * We can't use anon_inode_getfd() because we need to modify
	 * the f_mode flags directly to allow more than just ioctls
	 */
	ret = get_unused_fd_flags(O_CLOEXEC);
	if (ret < 0) {
		device->ops->release(device->device_data);
		vfio_device_put(device);
		return ret;
	}

	filep = anon_inode_getfile("[vfio-device]", &vfio_device_fops,
				   device, O_RDWR);
	if (IS_ERR(filep)) {
		put_unused_fd(ret);
		ret = PTR_ERR(filep);
		device->ops->release(device->device_data);
		vfio_device_put(device);
		return ret;
	}

	/*
	 * TODO: add an anon_inode interface to do this.
	 * Appears to be missing by lack of need rather than
	 * explicitly prevented.  Now there's need.
	 */
	filep->f_mode |= (FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);

	atomic_inc(&group->container_users);

	fd_install(ret, filep);

	if (group->noiommu)
		dev_warn(device->dev, "vfio-noiommu device opened by user "
			 "(%s:%d)\n", current->comm, task_pid_nr(current));

	return ret;
}