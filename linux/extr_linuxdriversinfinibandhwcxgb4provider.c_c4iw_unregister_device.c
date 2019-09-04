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
struct TYPE_2__ {int /*<<< orphan*/  iwcm; int /*<<< orphan*/  dev; } ;
struct c4iw_dev {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c4iw_class_attributes ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_dev*) ; 

void c4iw_unregister_device(struct c4iw_dev *dev)
{
	int i;

	pr_debug("c4iw_dev %p\n", dev);
	for (i = 0; i < ARRAY_SIZE(c4iw_class_attributes); ++i)
		device_remove_file(&dev->ibdev.dev,
				   c4iw_class_attributes[i]);
	ib_unregister_device(&dev->ibdev);
	kfree(dev->ibdev.iwcm);
	return;
}