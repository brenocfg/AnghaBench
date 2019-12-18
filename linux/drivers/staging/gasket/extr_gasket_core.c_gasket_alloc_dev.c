#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gasket_internal_desc {int /*<<< orphan*/  class; struct gasket_dev** devs; struct gasket_driver_desc* driver_desc; } ;
struct gasket_driver_desc {char* name; scalar_t__ minor; int /*<<< orphan*/  major; int /*<<< orphan*/  num_page_tables; } ;
struct gasket_cdev_info {struct gasket_dev* gasket_dev_ptr; int /*<<< orphan*/  name; int /*<<< orphan*/  devt; int /*<<< orphan*/  device; } ;
struct gasket_dev {int dev_idx; struct gasket_cdev_info dev_info; int /*<<< orphan*/  num_page_tables; int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj_name; struct gasket_internal_desc* internal_desc; int /*<<< orphan*/  mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GASKET_NAME_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct gasket_dev*,int /*<<< orphan*/ ) ; 
 int gasket_find_dev_slot (struct gasket_internal_desc*,char const*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct gasket_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int gasket_alloc_dev(struct gasket_internal_desc *internal_desc,
			    struct device *parent, struct gasket_dev **pdev)
{
	int dev_idx;
	const struct gasket_driver_desc *driver_desc =
		internal_desc->driver_desc;
	struct gasket_dev *gasket_dev;
	struct gasket_cdev_info *dev_info;
	const char *parent_name = dev_name(parent);

	pr_debug("Allocating a Gasket device, parent %s.\n", parent_name);

	*pdev = NULL;

	dev_idx = gasket_find_dev_slot(internal_desc, parent_name);
	if (dev_idx < 0)
		return dev_idx;

	gasket_dev = *pdev = kzalloc(sizeof(*gasket_dev), GFP_KERNEL);
	if (!gasket_dev) {
		pr_err("no memory for device, parent %s\n", parent_name);
		return -ENOMEM;
	}
	internal_desc->devs[dev_idx] = gasket_dev;

	mutex_init(&gasket_dev->mutex);

	gasket_dev->internal_desc = internal_desc;
	gasket_dev->dev_idx = dev_idx;
	snprintf(gasket_dev->kobj_name, GASKET_NAME_MAX, "%s", parent_name);
	gasket_dev->dev = get_device(parent);
	/* gasket_bar_data is uninitialized. */
	gasket_dev->num_page_tables = driver_desc->num_page_tables;
	/* max_page_table_size and *page table are uninit'ed */
	/* interrupt_data is not initialized. */
	/* status is 0, or GASKET_STATUS_DEAD */

	dev_info = &gasket_dev->dev_info;
	snprintf(dev_info->name, GASKET_NAME_MAX, "%s_%u", driver_desc->name,
		 gasket_dev->dev_idx);
	dev_info->devt =
		MKDEV(driver_desc->major, driver_desc->minor +
		      gasket_dev->dev_idx);
	dev_info->device =
		device_create(internal_desc->class, parent, dev_info->devt,
			      gasket_dev, dev_info->name);

	/* cdev has not yet been added; cdev_added is 0 */
	dev_info->gasket_dev_ptr = gasket_dev;
	/* ownership is all 0, indicating no owner or opens. */

	return 0;
}