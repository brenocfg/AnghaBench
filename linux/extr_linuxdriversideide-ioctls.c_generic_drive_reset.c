#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int cmd_len; int result; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRIV_MISC ; 
 int /*<<< orphan*/  REQ_DRIVE_RESET ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 TYPE_3__* ide_req (struct request*) ; 
 TYPE_2__* scsi_req (struct request*) ; 

__attribute__((used)) static int generic_drive_reset(ide_drive_t *drive)
{
	struct request *rq;
	int ret = 0;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	scsi_req(rq)->cmd_len = 1;
	scsi_req(rq)->cmd[0] = REQ_DRIVE_RESET;
	blk_execute_rq(drive->queue, NULL, rq, 1);
	ret = scsi_req(rq)->result;
	blk_put_request(rq);
	return ret;
}