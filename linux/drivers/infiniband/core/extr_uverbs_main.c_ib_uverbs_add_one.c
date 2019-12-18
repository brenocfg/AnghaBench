#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ devt; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/  class; } ;
struct TYPE_12__ {int /*<<< orphan*/  owner; } ;
struct ib_uverbs_device {int devnum; TYPE_3__ dev; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; TYPE_6__ cdev; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  uverbs_events_file_list; int /*<<< orphan*/  uverbs_file_list; int /*<<< orphan*/  lists_mutex; int /*<<< orphan*/  xrcd_tree_mutex; int /*<<< orphan*/  xrcd_tree; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  disassociate_srcu; } ;
struct TYPE_10__ {scalar_t__ mmap; int /*<<< orphan*/  alloc_ucontext; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_2__ ops; int /*<<< orphan*/  num_comp_vectors; TYPE_1__ dev; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_UVERBS_BASE_DEV ; 
 scalar_t__ IB_UVERBS_MAX_DEVICES ; 
 int IB_UVERBS_NUM_FIXED_MINOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int cdev_device_add (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_group ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 scalar_t__ dynamic_uverbs_dev ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_comp_dev (struct ib_uverbs_device*) ; 
 scalar_t__ ib_uverbs_create_uapi (struct ib_device*,struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_release_dev ; 
 int ida_alloc_max (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_uverbs_device*) ; 
 struct ib_uverbs_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ib_device*) ; 
 int /*<<< orphan*/  uverbs_class ; 
 int /*<<< orphan*/  uverbs_client ; 
 int /*<<< orphan*/  uverbs_fops ; 
 int /*<<< orphan*/  uverbs_ida ; 
 int /*<<< orphan*/  uverbs_mmap_fops ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_uverbs_add_one(struct ib_device *device)
{
	int devnum;
	dev_t base;
	struct ib_uverbs_device *uverbs_dev;
	int ret;

	if (!device->ops.alloc_ucontext)
		return;

	uverbs_dev = kzalloc(sizeof(*uverbs_dev), GFP_KERNEL);
	if (!uverbs_dev)
		return;

	ret = init_srcu_struct(&uverbs_dev->disassociate_srcu);
	if (ret) {
		kfree(uverbs_dev);
		return;
	}

	device_initialize(&uverbs_dev->dev);
	uverbs_dev->dev.class = uverbs_class;
	uverbs_dev->dev.parent = device->dev.parent;
	uverbs_dev->dev.release = ib_uverbs_release_dev;
	uverbs_dev->groups[0] = &dev_attr_group;
	uverbs_dev->dev.groups = uverbs_dev->groups;
	atomic_set(&uverbs_dev->refcount, 1);
	init_completion(&uverbs_dev->comp);
	uverbs_dev->xrcd_tree = RB_ROOT;
	mutex_init(&uverbs_dev->xrcd_tree_mutex);
	mutex_init(&uverbs_dev->lists_mutex);
	INIT_LIST_HEAD(&uverbs_dev->uverbs_file_list);
	INIT_LIST_HEAD(&uverbs_dev->uverbs_events_file_list);
	rcu_assign_pointer(uverbs_dev->ib_dev, device);
	uverbs_dev->num_comp_vectors = device->num_comp_vectors;

	devnum = ida_alloc_max(&uverbs_ida, IB_UVERBS_MAX_DEVICES - 1,
			       GFP_KERNEL);
	if (devnum < 0)
		goto err;
	uverbs_dev->devnum = devnum;
	if (devnum >= IB_UVERBS_NUM_FIXED_MINOR)
		base = dynamic_uverbs_dev + devnum - IB_UVERBS_NUM_FIXED_MINOR;
	else
		base = IB_UVERBS_BASE_DEV + devnum;

	if (ib_uverbs_create_uapi(device, uverbs_dev))
		goto err_uapi;

	uverbs_dev->dev.devt = base;
	dev_set_name(&uverbs_dev->dev, "uverbs%d", uverbs_dev->devnum);

	cdev_init(&uverbs_dev->cdev,
		  device->ops.mmap ? &uverbs_mmap_fops : &uverbs_fops);
	uverbs_dev->cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&uverbs_dev->cdev, &uverbs_dev->dev);
	if (ret)
		goto err_uapi;

	ib_set_client_data(device, &uverbs_client, uverbs_dev);
	return;

err_uapi:
	ida_free(&uverbs_ida, devnum);
err:
	if (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	wait_for_completion(&uverbs_dev->comp);
	put_device(&uverbs_dev->dev);
	return;
}