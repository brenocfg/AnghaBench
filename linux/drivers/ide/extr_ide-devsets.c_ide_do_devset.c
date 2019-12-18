#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
typedef  int /*<<< orphan*/  ide_drive_t ;
struct TYPE_4__ {int (* special ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  result; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ide_req (struct request*) ; 
 int /*<<< orphan*/  ide_stopped ; 
 TYPE_1__* scsi_req (struct request*) ; 

ide_startstop_t ide_do_devset(ide_drive_t *drive, struct request *rq)
{
	int err, (*setfunc)(ide_drive_t *, int) = ide_req(rq)->special;

	err = setfunc(drive, *(int *)&scsi_req(rq)->cmd[1]);
	if (err)
		scsi_req(rq)->result = err;
	ide_complete_rq(drive, 0, blk_rq_bytes(rq));
	return ide_stopped;
}