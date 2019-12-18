#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {void* size; void* subcommand; void* subcommand_length; int /*<<< orphan*/  buffer_address; void* buffer_length; } ;
struct TYPE_7__ {TYPE_1__ cmd; } ;
struct sns_cmd_pkt {TYPE_2__ p; } ;
struct qla_hw_data {int /*<<< orphan*/  sns_cmd_dma; struct sns_cmd_pkt* sns_cmd; } ;
struct TYPE_8__ {int /*<<< orphan*/  control_requests; } ;
struct TYPE_9__ {TYPE_3__ qla_stats; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct sns_cmd_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sns_cmd_pkt *
qla2x00_prep_sns_cmd(scsi_qla_host_t *vha, uint16_t cmd, uint16_t scmd_len,
    uint16_t data_size)
{
	uint16_t		wc;
	struct sns_cmd_pkt	*sns_cmd;
	struct qla_hw_data *ha = vha->hw;

	sns_cmd = ha->sns_cmd;
	memset(sns_cmd, 0, sizeof(struct sns_cmd_pkt));
	wc = data_size / 2;			/* Size in 16bit words. */
	sns_cmd->p.cmd.buffer_length = cpu_to_le16(wc);
	put_unaligned_le64(ha->sns_cmd_dma, &sns_cmd->p.cmd.buffer_address);
	sns_cmd->p.cmd.subcommand_length = cpu_to_le16(scmd_len);
	sns_cmd->p.cmd.subcommand = cpu_to_le16(cmd);
	wc = (data_size - 16) / 4;		/* Size in 32bit words. */
	sns_cmd->p.cmd.size = cpu_to_le16(wc);

	vha->qla_stats.control_requests++;

	return (sns_cmd);
}