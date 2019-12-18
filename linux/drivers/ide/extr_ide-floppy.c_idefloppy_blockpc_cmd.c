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
struct request {int dummy; } ;
struct ide_disk_obj {int dummy; } ;
struct ide_atapi_pc {int /*<<< orphan*/  flags; struct request* rq; int /*<<< orphan*/  c; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PC_FLAG_DMA_OK ; 
 int /*<<< orphan*/  PC_FLAG_WRITING ; 
 scalar_t__ WRITE ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static void idefloppy_blockpc_cmd(struct ide_disk_obj *floppy,
		struct ide_atapi_pc *pc, struct request *rq)
{
	ide_init_pc(pc);
	memcpy(pc->c, scsi_req(rq)->cmd, sizeof(pc->c));
	pc->rq = rq;
	if (blk_rq_bytes(rq)) {
		pc->flags |= PC_FLAG_DMA_OK;
		if (rq_data_dir(rq) == WRITE)
			pc->flags |= PC_FLAG_WRITING;
	}
}