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
typedef  int /*<<< orphan*/  u32 ;
struct ata_device {TYPE_1__* link; } ;
struct acpi_device {int /*<<< orphan*/  hp; } ;
struct TYPE_4__ {struct ata_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_handle_hotplug (int /*<<< orphan*/ ,struct ata_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__ ata_hotplug_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ata_acpi_dev_notify_dock(struct acpi_device *adev, u32 event)
{
	struct ata_device *dev = ata_hotplug_data(adev->hp).dev;
	ata_acpi_handle_hotplug(dev->link->ap, dev, event);
	return 0;
}