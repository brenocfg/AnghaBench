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
struct TYPE_2__ {int /*<<< orphan*/ * gfbdev; } ;
struct cirrus_device {TYPE_1__ mode_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_fbdev_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void cirrus_fbdev_fini(struct cirrus_device *cdev)
{
	if (!cdev->mode_info.gfbdev)
		return;

	cirrus_fbdev_destroy(cdev->dev, cdev->mode_info.gfbdev);
	kfree(cdev->mode_info.gfbdev);
	cdev->mode_info.gfbdev = NULL;
}