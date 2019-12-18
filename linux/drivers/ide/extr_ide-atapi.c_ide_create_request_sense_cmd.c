#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ide_atapi_pc {int* c; int req_xfer; } ;
struct TYPE_3__ {scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int REQUEST_SENSE ; 
 scalar_t__ ide_floppy ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 

void ide_create_request_sense_cmd(ide_drive_t *drive, struct ide_atapi_pc *pc)
{
	ide_init_pc(pc);
	pc->c[0] = REQUEST_SENSE;
	if (drive->media == ide_floppy) {
		pc->c[4] = 255;
		pc->req_xfer = 18;
	} else {
		pc->c[4] = 20;
		pc->req_xfer = 20;
	}
}