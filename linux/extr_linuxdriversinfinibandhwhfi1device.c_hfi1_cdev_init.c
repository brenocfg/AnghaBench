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
struct kobject {int dummy; } ;
struct file_operations {int dummy; } ;
struct device {int dummy; } ;
struct cdev {int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (struct cdev*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  cdev_del (struct cdev*) ; 
 int /*<<< orphan*/  cdev_init (struct cdev*,struct file_operations const*) ; 
 int /*<<< orphan*/  cdev_set_parent (struct cdev*,struct kobject*) ; 
 int /*<<< orphan*/  class ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  hfi1_dev ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,int,char const*,int) ; 
 int /*<<< orphan*/  user_class ; 

int hfi1_cdev_init(int minor, const char *name,
		   const struct file_operations *fops,
		   struct cdev *cdev, struct device **devp,
		   bool user_accessible,
		   struct kobject *parent)
{
	const dev_t dev = MKDEV(MAJOR(hfi1_dev), minor);
	struct device *device = NULL;
	int ret;

	cdev_init(cdev, fops);
	cdev->owner = THIS_MODULE;
	cdev_set_parent(cdev, parent);
	kobject_set_name(&cdev->kobj, name);

	ret = cdev_add(cdev, dev, 1);
	if (ret < 0) {
		pr_err("Could not add cdev for minor %d, %s (err %d)\n",
		       minor, name, -ret);
		goto done;
	}

	if (user_accessible)
		device = device_create(user_class, NULL, dev, NULL, "%s", name);
	else
		device = device_create(class, NULL, dev, NULL, "%s", name);

	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		device = NULL;
		pr_err("Could not create device for minor %d, %s (err %d)\n",
			minor, name, -ret);
		cdev_del(cdev);
	}
done:
	*devp = device;
	return ret;
}