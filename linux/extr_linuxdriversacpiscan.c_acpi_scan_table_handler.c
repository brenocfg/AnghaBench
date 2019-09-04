#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct acpi_table_events_work {int /*<<< orphan*/  work; scalar_t__ event; void* table; } ;

/* Variables and functions */
 scalar_t__ ACPI_TABLE_EVENT_LOAD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_scan_initialized ; 
 int /*<<< orphan*/  acpi_table_events_fn ; 
 struct acpi_table_events_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void acpi_scan_table_handler(u32 event, void *table, void *context)
{
	struct acpi_table_events_work *tew;

	if (!acpi_scan_initialized)
		return;

	if (event != ACPI_TABLE_EVENT_LOAD)
		return;

	tew = kmalloc(sizeof(*tew), GFP_KERNEL);
	if (!tew)
		return;

	INIT_WORK(&tew->work, acpi_table_events_fn);
	tew->table = table;
	tew->event = event;

	schedule_work(&tew->work);
}