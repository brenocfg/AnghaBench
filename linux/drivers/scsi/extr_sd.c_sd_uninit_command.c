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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {scalar_t__ cmd_len; int /*<<< orphan*/ * cmnd; struct request* request; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bv_page; } ;
struct request {int rq_flags; TYPE_1__ special_vec; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  sd_cdb_pool ; 
 int /*<<< orphan*/  sd_page_pool ; 

__attribute__((used)) static void sd_uninit_command(struct scsi_cmnd *SCpnt)
{
	struct request *rq = SCpnt->request;
	u8 *cmnd;

	if (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		mempool_free(rq->special_vec.bv_page, sd_page_pool);

	if (SCpnt->cmnd != scsi_req(rq)->cmd) {
		cmnd = SCpnt->cmnd;
		SCpnt->cmnd = NULL;
		SCpnt->cmd_len = 0;
		mempool_free(cmnd, sd_cdb_pool);
	}
}