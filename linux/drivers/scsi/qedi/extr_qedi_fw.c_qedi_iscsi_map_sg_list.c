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
struct TYPE_4__ {scalar_t__ hi; scalar_t__ lo; } ;
struct scsi_sge {scalar_t__ sge_len; TYPE_1__ sge_addr; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_5__ {int sge_valid; struct scsi_sge* sge_tbl; } ;
struct qedi_cmd {TYPE_2__ io_tbl; TYPE_3__* conn; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  qedi; } ;

/* Variables and functions */
 int qedi_map_scsi_sg (int /*<<< orphan*/ ,struct qedi_cmd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static void qedi_iscsi_map_sg_list(struct qedi_cmd *cmd)
{
	int bd_count;
	struct scsi_cmnd *sc = cmd->scsi_cmd;

	if (scsi_sg_count(sc)) {
		bd_count  = qedi_map_scsi_sg(cmd->conn->qedi, cmd);
		if (bd_count == 0)
			return;
	} else {
		struct scsi_sge *bd = cmd->io_tbl.sge_tbl;

		bd[0].sge_addr.lo = 0;
		bd[0].sge_addr.hi = 0;
		bd[0].sge_len = 0;
		bd_count = 0;
	}
	cmd->io_tbl.sge_valid = bd_count;
}