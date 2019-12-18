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
struct scsi_cmnd {int dummy; } ;
struct fcoe_bd_ctx {scalar_t__ flags; scalar_t__ buf_len; scalar_t__ buf_addr_hi; scalar_t__ buf_addr_lo; } ;
struct bnx2fc_cmd {int /*<<< orphan*/  xid; TYPE_1__* bd_tbl; struct scsi_cmnd* sc_cmd; } ;
struct TYPE_2__ {int bd_valid; struct fcoe_bd_ctx* bd_tbl; } ;

/* Variables and functions */
 int BNX2FC_FW_MAX_BDS_PER_CMD ; 
 int ENOMEM ; 
 int bnx2fc_map_sg (struct bnx2fc_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static int bnx2fc_build_bd_list_from_sg(struct bnx2fc_cmd *io_req)
{
	struct scsi_cmnd *sc = io_req->sc_cmd;
	struct fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	int bd_count;

	if (scsi_sg_count(sc)) {
		bd_count = bnx2fc_map_sg(io_req);
		if (bd_count == 0)
			return -ENOMEM;
	} else {
		bd_count = 0;
		bd[0].buf_addr_lo = bd[0].buf_addr_hi = 0;
		bd[0].buf_len = bd[0].flags = 0;
	}
	io_req->bd_tbl->bd_valid = bd_count;

	/*
	 * Return the command to ML if BD count exceeds the max number
	 * that can be handled by FW.
	 */
	if (bd_count > BNX2FC_FW_MAX_BDS_PER_CMD) {
		pr_err("bd_count = %d exceeded FW supported max BD(255), task_id = 0x%x\n",
		       bd_count, io_req->xid);
		return -ENOMEM;
	}

	return 0;
}