#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  disk; int /*<<< orphan*/  driver; } ;
typedef  TYPE_1__ idetape_tape_t ;
struct TYPE_6__ {TYPE_1__* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_proc_unregister_driver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_unregister_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idetape_ref_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_tape_remove(ide_drive_t *drive)
{
	idetape_tape_t *tape = drive->driver_data;

	ide_proc_unregister_driver(drive, tape->driver);
	device_del(&tape->dev);
	ide_unregister_region(tape->disk);

	mutex_lock(&idetape_ref_mutex);
	put_device(&tape->dev);
	mutex_unlock(&idetape_ref_mutex);
}