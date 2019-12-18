#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * fops; int /*<<< orphan*/  minor; } ;
struct ion_device {int /*<<< orphan*/  heaps; int /*<<< orphan*/  lock; int /*<<< orphan*/  debug_root; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct ion_device* internal_dev ; 
 int /*<<< orphan*/  ion_fops ; 
 int /*<<< orphan*/  kfree (struct ion_device*) ; 
 struct ion_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  plist_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ion_device_create(void)
{
	struct ion_device *idev;
	int ret;

	idev = kzalloc(sizeof(*idev), GFP_KERNEL);
	if (!idev)
		return -ENOMEM;

	idev->dev.minor = MISC_DYNAMIC_MINOR;
	idev->dev.name = "ion";
	idev->dev.fops = &ion_fops;
	idev->dev.parent = NULL;
	ret = misc_register(&idev->dev);
	if (ret) {
		pr_err("ion: failed to register misc device.\n");
		kfree(idev);
		return ret;
	}

	idev->debug_root = debugfs_create_dir("ion", NULL);
	init_rwsem(&idev->lock);
	plist_head_init(&idev->heaps);
	internal_dev = idev;
	return 0;
}