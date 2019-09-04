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
typedef  int u8 ;
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
typedef  int /*<<< orphan*/  ide_drive_t ;
struct TYPE_2__ {int* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  REQ_DEVSET_EXEC 131 
#define  REQ_DRIVE_RESET 130 
#define  REQ_PARK_HEADS 129 
#define  REQ_UNPARK_HEADS 128 
 int /*<<< orphan*/  ide_do_devset (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  ide_do_park_unpark (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  ide_do_reset (int /*<<< orphan*/ *) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static ide_startstop_t ide_special_rq(ide_drive_t *drive, struct request *rq)
{
	u8 cmd = scsi_req(rq)->cmd[0];

	switch (cmd) {
	case REQ_PARK_HEADS:
	case REQ_UNPARK_HEADS:
		return ide_do_park_unpark(drive, rq);
	case REQ_DEVSET_EXEC:
		return ide_do_devset(drive, rq);
	case REQ_DRIVE_RESET:
		return ide_do_reset(drive);
	default:
		BUG();
	}
}