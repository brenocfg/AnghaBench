#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ devt; int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  release; } ;
struct TYPE_13__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; } ;
struct ib_ucm_device {int devnum; TYPE_2__ dev; TYPE_6__ cdev; struct ib_device* ib_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_1__ dev; int /*<<< orphan*/  alloc_ucontext; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_UCM_BASE_DEV ; 
 int IB_UCM_MAX_DEVICES ; 
 int IB_UCM_NUM_FIXED_MINOR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ cdev_device_add (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_device_del (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_class ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_map ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int) ; 
 scalar_t__ device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 scalar_t__ dynamic_ucm_dev ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_ucm_device*) ; 
 int /*<<< orphan*/  ib_ucm_free_dev (struct ib_ucm_device*) ; 
 int /*<<< orphan*/  ib_ucm_release_dev ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,int) ; 
 struct ib_ucm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_cap_ib_cm (struct ib_device*,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucm_client ; 
 int /*<<< orphan*/  ucm_fops ; 

__attribute__((used)) static void ib_ucm_add_one(struct ib_device *device)
{
	int devnum;
	dev_t base;
	struct ib_ucm_device *ucm_dev;

	if (!device->alloc_ucontext || !rdma_cap_ib_cm(device, 1))
		return;

	ucm_dev = kzalloc(sizeof *ucm_dev, GFP_KERNEL);
	if (!ucm_dev)
		return;

	device_initialize(&ucm_dev->dev);
	ucm_dev->ib_dev = device;
	ucm_dev->dev.release = ib_ucm_release_dev;

	devnum = find_first_zero_bit(dev_map, IB_UCM_MAX_DEVICES);
	if (devnum >= IB_UCM_MAX_DEVICES)
		goto err;
	ucm_dev->devnum = devnum;
	set_bit(devnum, dev_map);
	if (devnum >= IB_UCM_NUM_FIXED_MINOR)
		base = dynamic_ucm_dev + devnum - IB_UCM_NUM_FIXED_MINOR;
	else
		base = IB_UCM_BASE_DEV + devnum;

	cdev_init(&ucm_dev->cdev, &ucm_fops);
	ucm_dev->cdev.owner = THIS_MODULE;
	kobject_set_name(&ucm_dev->cdev.kobj, "ucm%d", ucm_dev->devnum);

	ucm_dev->dev.class = &cm_class;
	ucm_dev->dev.parent = device->dev.parent;
	ucm_dev->dev.devt = base;

	dev_set_name(&ucm_dev->dev, "ucm%d", ucm_dev->devnum);
	if (cdev_device_add(&ucm_dev->cdev, &ucm_dev->dev))
		goto err_devnum;

	if (device_create_file(&ucm_dev->dev, &dev_attr_ibdev))
		goto err_dev;

	ib_set_client_data(device, &ucm_client, ucm_dev);
	return;

err_dev:
	cdev_device_del(&ucm_dev->cdev, &ucm_dev->dev);
err_devnum:
	ib_ucm_free_dev(ucm_dev);
err:
	put_device(&ucm_dev->dev);
	return;
}