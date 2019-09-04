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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct inode {int /*<<< orphan*/  i_rdev; struct cdev* i_cdev; } ;
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; struct device* parent; int /*<<< orphan*/  class; int /*<<< orphan*/  devt; TYPE_2__* driver; } ;
struct dev_dax {int id; int num_resources; struct dax_region* region; struct dax_device* dax_dev; struct device dev; TYPE_1__* res; } ;
struct dax_region {int /*<<< orphan*/  ida; struct device* dev; int /*<<< orphan*/  id; int /*<<< orphan*/  kref; int /*<<< orphan*/  align; } ;
struct dax_device {int dummy; } ;
struct cdev {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct dev_dax* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dax_device* alloc_dax (struct dev_dax*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cdev_device_add (struct cdev*,struct device*) ; 
 int /*<<< orphan*/  cdev_init (struct cdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_attribute_groups ; 
 int /*<<< orphan*/  dax_class ; 
 int /*<<< orphan*/  dax_fops ; 
 struct inode* dax_inode (struct dax_device*) ; 
 int /*<<< orphan*/  dev_dax_release ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct dev_dax*) ; 
 int /*<<< orphan*/  kill_dev_dax (struct dev_dax*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct dev_dax* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  struct_size (struct dev_dax*,struct resource*,int) ; 
 int /*<<< orphan*/  unregister_dev_dax ; 

struct dev_dax *devm_create_dev_dax(struct dax_region *dax_region,
		int id, struct resource *res, int count)
{
	struct device *parent = dax_region->dev;
	struct dax_device *dax_dev;
	struct dev_dax *dev_dax;
	struct inode *inode;
	struct device *dev;
	struct cdev *cdev;
	int rc, i;

	if (!count)
		return ERR_PTR(-EINVAL);

	dev_dax = kzalloc(struct_size(dev_dax, res, count), GFP_KERNEL);
	if (!dev_dax)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < count; i++) {
		if (!IS_ALIGNED(res[i].start, dax_region->align)
				|| !IS_ALIGNED(resource_size(&res[i]),
					dax_region->align)) {
			rc = -EINVAL;
			break;
		}
		dev_dax->res[i].start = res[i].start;
		dev_dax->res[i].end = res[i].end;
	}

	if (i < count)
		goto err_id;

	if (id < 0) {
		id = ida_simple_get(&dax_region->ida, 0, 0, GFP_KERNEL);
		dev_dax->id = id;
		if (id < 0) {
			rc = id;
			goto err_id;
		}
	} else {
		/* region provider owns @id lifetime */
		dev_dax->id = -1;
	}

	/*
	 * No 'host' or dax_operations since there is no access to this
	 * device outside of mmap of the resulting character device.
	 */
	dax_dev = alloc_dax(dev_dax, NULL, NULL);
	if (!dax_dev) {
		rc = -ENOMEM;
		goto err_dax;
	}

	/* from here on we're committed to teardown via dax_dev_release() */
	dev = &dev_dax->dev;
	device_initialize(dev);

	inode = dax_inode(dax_dev);
	cdev = inode->i_cdev;
	cdev_init(cdev, &dax_fops);
	cdev->owner = parent->driver->owner;

	dev_dax->num_resources = count;
	dev_dax->dax_dev = dax_dev;
	dev_dax->region = dax_region;
	kref_get(&dax_region->kref);

	dev->devt = inode->i_rdev;
	dev->class = dax_class;
	dev->parent = parent;
	dev->groups = dax_attribute_groups;
	dev->release = dev_dax_release;
	dev_set_name(dev, "dax%d.%d", dax_region->id, id);

	rc = cdev_device_add(cdev, dev);
	if (rc) {
		kill_dev_dax(dev_dax);
		put_device(dev);
		return ERR_PTR(rc);
	}

	rc = devm_add_action_or_reset(dax_region->dev, unregister_dev_dax, dev);
	if (rc)
		return ERR_PTR(rc);

	return dev_dax;

 err_dax:
	if (dev_dax->id >= 0)
		ida_simple_remove(&dax_region->ida, dev_dax->id);
 err_id:
	kfree(dev_dax);

	return ERR_PTR(rc);
}