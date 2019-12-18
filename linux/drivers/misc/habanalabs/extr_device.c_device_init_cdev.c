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
struct hl_device {int /*<<< orphan*/  major; } ;
struct file_operations {int dummy; } ;
struct device {int /*<<< orphan*/  release; struct class* class; int /*<<< orphan*/  devt; } ;
struct class {int dummy; } ;
struct cdev {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cdev_init (struct cdev*,struct file_operations const*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct hl_device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,char*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  device_release_func ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_init_cdev(struct hl_device *hdev, struct class *hclass,
				int minor, const struct file_operations *fops,
				char *name, struct cdev *cdev,
				struct device **dev)
{
	cdev_init(cdev, fops);
	cdev->owner = THIS_MODULE;

	*dev = kzalloc(sizeof(**dev), GFP_KERNEL);
	if (!*dev)
		return -ENOMEM;

	device_initialize(*dev);
	(*dev)->devt = MKDEV(hdev->major, minor);
	(*dev)->class = hclass;
	(*dev)->release = device_release_func;
	dev_set_drvdata(*dev, hdev);
	dev_set_name(*dev, "%s", name);

	return 0;
}