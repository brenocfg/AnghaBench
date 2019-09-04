#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_driver {int /*<<< orphan*/  (* proc_entries ) (TYPE_1__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * settings; int /*<<< orphan*/  proc; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_remove_proc_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_setting_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void ide_proc_unregister_driver(ide_drive_t *drive, struct ide_driver *driver)
{
	ide_remove_proc_entries(drive->proc, driver->proc_entries(drive));

	mutex_lock(&ide_setting_mtx);
	/*
	 * ide_setting_mtx protects both the settings list and the use
	 * of settings (we cannot take a setting out that is being used).
	 */
	drive->settings = NULL;
	mutex_unlock(&ide_setting_mtx);
}