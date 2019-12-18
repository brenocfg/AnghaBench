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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fieldbus_dev {int /*<<< orphan*/  id; TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fieldbus_class ; 
 int /*<<< orphan*/  fieldbus_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fieldbus_dev_unregister(struct fieldbus_dev *fb)
{
	if (!fb)
		return;
	device_destroy(&fieldbus_class, fb->cdev.dev);
	cdev_del(&fb->cdev);
	ida_simple_remove(&fieldbus_ida, fb->id);
}