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
struct adxl34x {TYPE_1__* dev; int /*<<< orphan*/  input; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  adxl34x_attr_group ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adxl34x*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adxl34x*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int adxl34x_remove(struct adxl34x *ac)
{
	sysfs_remove_group(&ac->dev->kobj, &adxl34x_attr_group);
	free_irq(ac->irq, ac);
	input_unregister_device(ac->input);
	dev_dbg(ac->dev, "unregistered accelerometer\n");
	kfree(ac);

	return 0;
}