#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rdma_dev_net {int /*<<< orphan*/  id; int /*<<< orphan*/  net; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdma_net; } ;
struct ib_device {int /*<<< orphan*/  compat_devs_mutex; int /*<<< orphan*/  compat_devs; TYPE_6__ dev; TYPE_1__ coredev; } ;
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct ib_core_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  compatdev_release ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_devices_shared_netns ; 
 int /*<<< orphan*/  ib_free_port_attrs (struct ib_core_device*) ; 
 int ib_setup_port_attrs (struct ib_core_device*) ; 
 struct ib_core_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_init_coredev (struct ib_core_device*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_nets_rwsem ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 
 int xa_err (int /*<<< orphan*/ ) ; 
 struct ib_core_device* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xa_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ib_core_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_one_compat_dev(struct ib_device *device,
			      struct rdma_dev_net *rnet)
{
	struct ib_core_device *cdev;
	int ret;

	lockdep_assert_held(&rdma_nets_rwsem);
	if (!ib_devices_shared_netns)
		return 0;

	/*
	 * Create and add compat device in all namespaces other than where it
	 * is currently bound to.
	 */
	if (net_eq(read_pnet(&rnet->net),
		   read_pnet(&device->coredev.rdma_net)))
		return 0;

	/*
	 * The first of init_net() or ib_register_device() to take the
	 * compat_devs_mutex wins and gets to add the device. Others will wait
	 * for completion here.
	 */
	mutex_lock(&device->compat_devs_mutex);
	cdev = xa_load(&device->compat_devs, rnet->id);
	if (cdev) {
		ret = 0;
		goto done;
	}
	ret = xa_reserve(&device->compat_devs, rnet->id, GFP_KERNEL);
	if (ret)
		goto done;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev) {
		ret = -ENOMEM;
		goto cdev_err;
	}

	cdev->dev.parent = device->dev.parent;
	rdma_init_coredev(cdev, device, read_pnet(&rnet->net));
	cdev->dev.release = compatdev_release;
	dev_set_name(&cdev->dev, "%s", dev_name(&device->dev));

	ret = device_add(&cdev->dev);
	if (ret)
		goto add_err;
	ret = ib_setup_port_attrs(cdev);
	if (ret)
		goto port_err;

	ret = xa_err(xa_store(&device->compat_devs, rnet->id,
			      cdev, GFP_KERNEL));
	if (ret)
		goto insert_err;

	mutex_unlock(&device->compat_devs_mutex);
	return 0;

insert_err:
	ib_free_port_attrs(cdev);
port_err:
	device_del(&cdev->dev);
add_err:
	put_device(&cdev->dev);
cdev_err:
	xa_release(&device->compat_devs, rnet->id);
done:
	mutex_unlock(&device->compat_devs_mutex);
	return ret;
}