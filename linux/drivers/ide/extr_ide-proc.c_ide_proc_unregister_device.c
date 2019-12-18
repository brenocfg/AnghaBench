#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int /*<<< orphan*/ * proc; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {int /*<<< orphan*/ * proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_drive_entries ; 
 int /*<<< orphan*/  ide_remove_proc_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_ide_root ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

void ide_proc_unregister_device(ide_drive_t *drive)
{
	if (drive->proc) {
		remove_proc_entry("settings", drive->proc);
		ide_remove_proc_entries(drive->proc, generic_drive_entries);
		remove_proc_entry(drive->name, proc_ide_root);
		remove_proc_entry(drive->name, drive->hwif->proc);
		drive->proc = NULL;
	}
}