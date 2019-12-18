#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * param; } ;
struct TYPE_14__ {int* rnn_data; TYPE_3__ cmd; } ;
struct sns_cmd_pkt {TYPE_4__ p; } ;
struct qla_hw_data {int /*<<< orphan*/  sns_cmd_dma; } ;
struct TYPE_11__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_12__ {TYPE_1__ b; } ;
struct TYPE_15__ {int /*<<< orphan*/ * node_name; TYPE_2__ d_id; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;

/* Variables and functions */
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RNN_ID_CMD ; 
 int RNN_ID_SNS_CMD_SIZE ; 
 int /*<<< orphan*/  RNN_ID_SNS_DATA_SIZE ; 
 int /*<<< orphan*/  RNN_ID_SNS_SCMD_LEN ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_5__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_5__*,int,int*,int) ; 
 struct sns_cmd_pkt* qla2x00_prep_sns_cmd (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qla2x00_send_sns (TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
qla2x00_sns_rnn_id(scsi_qla_host_t *vha)
{
	int		rval;
	struct qla_hw_data *ha = vha->hw;
	struct sns_cmd_pkt	*sns_cmd;

	/* Issue RNN_ID. */
	/* Prepare SNS command request. */
	sns_cmd = qla2x00_prep_sns_cmd(vha, RNN_ID_CMD, RNN_ID_SNS_SCMD_LEN,
	    RNN_ID_SNS_DATA_SIZE);

	/* Prepare SNS command arguments -- port_id, nodename. */
	sns_cmd->p.cmd.param[0] = vha->d_id.b.al_pa;
	sns_cmd->p.cmd.param[1] = vha->d_id.b.area;
	sns_cmd->p.cmd.param[2] = vha->d_id.b.domain;

	sns_cmd->p.cmd.param[4] = vha->node_name[7];
	sns_cmd->p.cmd.param[5] = vha->node_name[6];
	sns_cmd->p.cmd.param[6] = vha->node_name[5];
	sns_cmd->p.cmd.param[7] = vha->node_name[4];
	sns_cmd->p.cmd.param[8] = vha->node_name[3];
	sns_cmd->p.cmd.param[9] = vha->node_name[2];
	sns_cmd->p.cmd.param[10] = vha->node_name[1];
	sns_cmd->p.cmd.param[11] = vha->node_name[0];

	/* Execute SNS command. */
	rval = qla2x00_send_sns(vha, ha->sns_cmd_dma, RNN_ID_SNS_CMD_SIZE / 2,
	    sizeof(struct sns_cmd_pkt));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x204a,
		    "RNN_ID Send SNS failed (%d).\n", rval);
	} else if (sns_cmd->p.rnn_data[8] != 0x80 ||
	    sns_cmd->p.rnn_data[9] != 0x02) {
		ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x207b,
		    "RNN_ID failed, rejected request, rnn_rsp:\n");
		ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x207c,
		    sns_cmd->p.rnn_data, 16);
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x204c,
		    "RNN_ID exiting normally.\n");
	}

	return (rval);
}