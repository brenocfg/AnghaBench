#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {TYPE_1__* handler; } ;
struct scsi_cmnd {int /*<<< orphan*/  cmnd; } ;
struct request {int dummy; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_6__ {scalar_t__ (* init_command ) (struct scsi_cmnd*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  __cmd; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {scalar_t__ (* prep_fn ) (struct scsi_device*,struct request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MAX_CDB ; 
 scalar_t__ BLK_STS_OK ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* scsi_cmd_to_driver (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_req (struct request*) ; 
 scalar_t__ stub1 (struct scsi_device*,struct request*) ; 
 scalar_t__ stub2 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t scsi_setup_fs_cmnd(struct scsi_device *sdev,
		struct request *req)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);

	if (unlikely(sdev->handler && sdev->handler->prep_fn)) {
		blk_status_t ret = sdev->handler->prep_fn(sdev, req);
		if (ret != BLK_STS_OK)
			return ret;
	}

	cmd->cmnd = scsi_req(req)->cmd = scsi_req(req)->__cmd;
	memset(cmd->cmnd, 0, BLK_MAX_CDB);
	return scsi_cmd_to_driver(cmd)->init_command(cmd);
}