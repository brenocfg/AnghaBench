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
struct scsi_ctrl_blk {int dummy; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct initio_host {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int SCSI_MLQUEUE_HOST_BUSY ; 
 struct scsi_ctrl_blk* initio_alloc_scb (struct initio_host*) ; 
 int /*<<< orphan*/  initio_build_scb (struct initio_host*,struct scsi_ctrl_blk*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  initio_exec_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 

__attribute__((used)) static int i91u_queuecommand_lck(struct scsi_cmnd *cmd,
		void (*done)(struct scsi_cmnd *))
{
	struct initio_host *host = (struct initio_host *) cmd->device->host->hostdata;
	struct scsi_ctrl_blk *cmnd;

	cmd->scsi_done = done;

	cmnd = initio_alloc_scb(host);
	if (!cmnd)
		return SCSI_MLQUEUE_HOST_BUSY;

	initio_build_scb(host, cmnd, cmd);
	initio_exec_scb(host, cmnd);
	return 0;
}