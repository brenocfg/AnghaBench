#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_disable_gpe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_remove_gpe_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_2__ lid_wake_on_close_attr ; 
 int /*<<< orphan*/  sci_work ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo15_sci_gpe ; 
 int /*<<< orphan*/  xo15_sci_gpe_handler ; 

__attribute__((used)) static int xo15_sci_remove(struct acpi_device *device)
{
	acpi_disable_gpe(NULL, xo15_sci_gpe);
	acpi_remove_gpe_handler(NULL, xo15_sci_gpe, xo15_sci_gpe_handler);
	cancel_work_sync(&sci_work);
	sysfs_remove_file(&device->dev.kobj, &lid_wake_on_close_attr.attr);
	return 0;
}