#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  controlvm_channel; TYPE_2__* acpi_device; int /*<<< orphan*/  periodic_controlvm_work; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_3__* chipset_dev ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visorbus_exit () ; 
 int /*<<< orphan*/  visorchannel_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visorchipset_dev_groups ; 

__attribute__((used)) static int visorchipset_exit(struct acpi_device *acpi_device)
{
	visorbus_exit();
	cancel_delayed_work_sync(&chipset_dev->periodic_controlvm_work);
	sysfs_remove_groups(&chipset_dev->acpi_device->dev.kobj,
			    visorchipset_dev_groups);
	visorchannel_destroy(chipset_dev->controlvm_channel);
	kfree(chipset_dev);
	return 0;
}