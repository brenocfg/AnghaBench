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
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/  allowed; scalar_t__ transfersize; int /*<<< orphan*/ * cmnd; int /*<<< orphan*/  sdb; struct request* request; } ;
struct request {int timeout; TYPE_1__* q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int SD_FLUSH_TIMEOUT_MULTIPLIER ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SYNCHRONIZE_CACHE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static blk_status_t sd_setup_flush_cmnd(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;

	/* flush requests don't perform I/O, zero the S/G table */
	memset(&cmd->sdb, 0, sizeof(cmd->sdb));

	cmd->cmnd[0] = SYNCHRONIZE_CACHE;
	cmd->cmd_len = 10;
	cmd->transfersize = 0;
	cmd->allowed = SD_MAX_RETRIES;

	rq->timeout = rq->q->rq_timeout * SD_FLUSH_TIMEOUT_MULTIPLIER;
	return BLK_STS_OK;
}