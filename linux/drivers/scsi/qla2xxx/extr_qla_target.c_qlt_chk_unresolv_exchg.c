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
typedef  int /*<<< orphan*/  uint8_t ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
struct qla_qpair {scalar_t__ retry_term_exchg_addr; scalar_t__ retry_term_jiff; int retry_term_cnt; } ;
struct qla_hw_data {TYPE_1__* isp_ops; struct qla_qpair* base_qpair; } ;
struct abts_resp_from_24xx_fw {scalar_t__ exchange_addr_to_abort; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fw_dump ) (struct scsi_qla_host*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ jiffies ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,struct scsi_qla_host*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*,int) ; 

__attribute__((used)) static int qlt_chk_unresolv_exchg(struct scsi_qla_host *vha,
    struct qla_qpair *qpair, struct abts_resp_from_24xx_fw *entry)
{
	struct qla_hw_data *ha = vha->hw;
	int rc = 0;

	/*
	 * Detect unresolved exchange. If the same ABTS is unable
	 * to terminate an existing command and the same ABTS loops
	 * between FW & Driver, then force FW dump. Under 1 jiff,
	 * we should see multiple loops.
	 */
	if (qpair->retry_term_exchg_addr == entry->exchange_addr_to_abort &&
	    qpair->retry_term_jiff == jiffies) {
		/* found existing exchange */
		qpair->retry_term_cnt++;
		if (qpair->retry_term_cnt >= 5) {
			rc = EIO;
			qpair->retry_term_cnt = 0;
			ql_log(ql_log_warn, vha, 0xffff,
			    "Unable to send ABTS Respond. Dumping firmware.\n");
			ql_dump_buffer(ql_dbg_tgt_mgt + ql_dbg_buffer,
			    vha, 0xffff, (uint8_t *)entry, sizeof(*entry));

			if (qpair == ha->base_qpair)
				ha->isp_ops->fw_dump(vha, 1);
			else
				ha->isp_ops->fw_dump(vha, 0);

			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		}
	} else if (qpair->retry_term_jiff != jiffies) {
		qpair->retry_term_exchg_addr = entry->exchange_addr_to_abort;
		qpair->retry_term_cnt = 0;
		qpair->retry_term_jiff = jiffies;
	}

	return rc;
}