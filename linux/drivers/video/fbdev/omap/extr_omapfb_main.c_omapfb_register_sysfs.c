#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omapfb_device {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_attr_grp ; 
 int /*<<< orphan*/  dev_attr_caps_num ; 
 int /*<<< orphan*/  dev_attr_caps_text ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_attr_grp ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omapfb_register_sysfs(struct omapfb_device *fbdev)
{
	int r;

	if ((r = device_create_file(fbdev->dev, &dev_attr_caps_num)))
		goto fail0;

	if ((r = device_create_file(fbdev->dev, &dev_attr_caps_text)))
		goto fail1;

	if ((r = sysfs_create_group(&fbdev->dev->kobj, &panel_attr_grp)))
		goto fail2;

	if ((r = sysfs_create_group(&fbdev->dev->kobj, &ctrl_attr_grp)))
		goto fail3;

	return 0;
fail3:
	sysfs_remove_group(&fbdev->dev->kobj, &panel_attr_grp);
fail2:
	device_remove_file(fbdev->dev, &dev_attr_caps_text);
fail1:
	device_remove_file(fbdev->dev, &dev_attr_caps_num);
fail0:
	dev_err(fbdev->dev, "unable to register sysfs interface\n");
	return r;
}