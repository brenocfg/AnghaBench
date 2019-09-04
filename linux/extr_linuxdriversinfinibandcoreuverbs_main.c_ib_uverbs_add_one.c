#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct ib_uverbs_device {int devnum; int /*<<< orphan*/  kobj; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; TYPE_2__ cdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  uverbs_events_file_list; int /*<<< orphan*/  uverbs_file_list; int /*<<< orphan*/  lists_mutex; int /*<<< orphan*/  xrcd_tree_mutex; int /*<<< orphan*/  xrcd_tree; int /*<<< orphan*/  disassociate_srcu; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_1__ dev; scalar_t__ mmap; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  alloc_ucontext; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_UVERBS_BASE_DEV ; 
 int IB_UVERBS_MAX_DEVICES ; 
 int IB_UVERBS_NUM_FIXED_MINOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cdev_add (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_set_parent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_abi_version ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_map ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_uverbs_device*,char*,int) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dynamic_uverbs_dev ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_comp_dev (struct ib_uverbs_device*) ; 
 scalar_t__ ib_uverbs_create_uapi (struct ib_device*,struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_dev_ktype ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,int) ; 
 struct ib_uverbs_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ib_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uverbs_class ; 
 int /*<<< orphan*/  uverbs_client ; 
 int /*<<< orphan*/  uverbs_fops ; 
 int /*<<< orphan*/  uverbs_mmap_fops ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_uverbs_add_one(struct ib_device *device)
{
	int devnum;
	dev_t base;
	struct ib_uverbs_device *uverbs_dev;
	int ret;

	if (!device->alloc_ucontext)
		return;

	uverbs_dev = kzalloc(sizeof(*uverbs_dev), GFP_KERNEL);
	if (!uverbs_dev)
		return;

	ret = init_srcu_struct(&uverbs_dev->disassociate_srcu);
	if (ret) {
		kfree(uverbs_dev);
		return;
	}

	atomic_set(&uverbs_dev->refcount, 1);
	init_completion(&uverbs_dev->comp);
	uverbs_dev->xrcd_tree = RB_ROOT;
	mutex_init(&uverbs_dev->xrcd_tree_mutex);
	kobject_init(&uverbs_dev->kobj, &ib_uverbs_dev_ktype);
	mutex_init(&uverbs_dev->lists_mutex);
	INIT_LIST_HEAD(&uverbs_dev->uverbs_file_list);
	INIT_LIST_HEAD(&uverbs_dev->uverbs_events_file_list);

	devnum = find_first_zero_bit(dev_map, IB_UVERBS_MAX_DEVICES);
	if (devnum >= IB_UVERBS_MAX_DEVICES)
		goto err;
	uverbs_dev->devnum = devnum;
	set_bit(devnum, dev_map);
	if (devnum >= IB_UVERBS_NUM_FIXED_MINOR)
		base = dynamic_uverbs_dev + devnum - IB_UVERBS_NUM_FIXED_MINOR;
	else
		base = IB_UVERBS_BASE_DEV + devnum;

	rcu_assign_pointer(uverbs_dev->ib_dev, device);
	uverbs_dev->num_comp_vectors = device->num_comp_vectors;

	if (ib_uverbs_create_uapi(device, uverbs_dev))
		goto err_uapi;

	cdev_init(&uverbs_dev->cdev, NULL);
	uverbs_dev->cdev.owner = THIS_MODULE;
	uverbs_dev->cdev.ops = device->mmap ? &uverbs_mmap_fops : &uverbs_fops;
	cdev_set_parent(&uverbs_dev->cdev, &uverbs_dev->kobj);
	kobject_set_name(&uverbs_dev->cdev.kobj, "uverbs%d", uverbs_dev->devnum);
	if (cdev_add(&uverbs_dev->cdev, base, 1))
		goto err_cdev;

	uverbs_dev->dev = device_create(uverbs_class, device->dev.parent,
					uverbs_dev->cdev.dev, uverbs_dev,
					"uverbs%d", uverbs_dev->devnum);
	if (IS_ERR(uverbs_dev->dev))
		goto err_cdev;

	if (device_create_file(uverbs_dev->dev, &dev_attr_ibdev))
		goto err_class;
	if (device_create_file(uverbs_dev->dev, &dev_attr_abi_version))
		goto err_class;

	ib_set_client_data(device, &uverbs_client, uverbs_dev);

	return;

err_class:
	device_destroy(uverbs_class, uverbs_dev->cdev.dev);
err_cdev:
	cdev_del(&uverbs_dev->cdev);
err_uapi:
	clear_bit(devnum, dev_map);
err:
	if (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	wait_for_completion(&uverbs_dev->comp);
	kobject_put(&uverbs_dev->kobj);
	return;
}