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
typedef  int u32 ;
struct ata_eh_info {int dummy; } ;
struct TYPE_2__ {struct ata_eh_info eh_info; } ;
struct ata_port {int /*<<< orphan*/  lock; TYPE_1__ link; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 130 
#define  ACPI_NOTIFY_DEVICE_CHECK 129 
#define  ACPI_NOTIFY_EJECT_REQUEST 128 
 int /*<<< orphan*/  ata_acpi_detach_device (struct ata_port*,struct ata_device*) ; 
 int /*<<< orphan*/  ata_ehi_hotplugged (struct ata_eh_info*) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_wait_eh (struct ata_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ata_acpi_handle_hotplug(struct ata_port *ap, struct ata_device *dev,
				    u32 event)
{
	struct ata_eh_info *ehi = &ap->link.eh_info;
	int wait = 0;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);
	/*
	 * When dock driver calls into the routine, it will always use
	 * ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK for add and
	 * ACPI_NOTIFY_EJECT_REQUEST for remove
	 */
	switch (event) {
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_ehi_hotplugged(ehi);
		ata_port_freeze(ap);
		break;
	case ACPI_NOTIFY_EJECT_REQUEST:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_acpi_detach_device(ap, dev);
		wait = 1;
		break;
	}

	spin_unlock_irqrestore(ap->lock, flags);

	if (wait)
		ata_port_wait_eh(ap);
}