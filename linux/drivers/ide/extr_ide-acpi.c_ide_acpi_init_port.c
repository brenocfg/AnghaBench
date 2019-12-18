#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ide_acpi_hwif_link {int dummy; } ;
struct TYPE_6__ {TYPE_2__* acpidata; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int /*<<< orphan*/  obj_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ide_acpi_hwif_get_handle (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

void ide_acpi_init_port(ide_hwif_t *hwif)
{
	hwif->acpidata = kzalloc(sizeof(struct ide_acpi_hwif_link), GFP_KERNEL);
	if (!hwif->acpidata)
		return;

	hwif->acpidata->obj_handle = ide_acpi_hwif_get_handle(hwif);
	if (!hwif->acpidata->obj_handle) {
		DEBPRINT("no ACPI object for %s found\n", hwif->name);
		kfree(hwif->acpidata);
		hwif->acpidata = NULL;
	}
}