#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ide_tape_obj {int /*<<< orphan*/  disk; } ;
struct ide_atapi_pc {int dummy; } ;
struct TYPE_6__ {struct ide_tape_obj* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int HZ ; 
 int ide_queue_pc_tail (TYPE_1__*,int /*<<< orphan*/ ,struct ide_atapi_pc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idetape_create_write_filemark_cmd (TYPE_1__*,struct ide_atapi_pc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idetape_wait_ready (TYPE_1__*,int) ; 

__attribute__((used)) static int idetape_flush_tape_buffers(ide_drive_t *drive)
{
	struct ide_tape_obj *tape = drive->driver_data;
	struct ide_atapi_pc pc;
	int rc;

	idetape_create_write_filemark_cmd(drive, &pc, 0);
	rc = ide_queue_pc_tail(drive, tape->disk, &pc, NULL, 0);
	if (rc)
		return rc;
	idetape_wait_ready(drive, 60 * 5 * HZ);
	return 0;
}