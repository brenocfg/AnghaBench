#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int postponed_rq; int /*<<< orphan*/  dsc_poll_freq; } ;
typedef  TYPE_3__ idetape_tape_t ;
struct TYPE_10__ {TYPE_2__* hwif; TYPE_3__* driver_data; } ;
typedef  TYPE_4__ ide_drive_t ;
struct TYPE_8__ {TYPE_1__* rq; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_stall_queue (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ide_tape_stall_queue(ide_drive_t *drive)
{
	idetape_tape_t *tape = drive->driver_data;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, dsc_poll_freq: %lu",
		      drive->hwif->rq->cmd[0], tape->dsc_poll_freq);

	tape->postponed_rq = true;

	ide_stall_queue(drive, tape->dsc_poll_freq);
}