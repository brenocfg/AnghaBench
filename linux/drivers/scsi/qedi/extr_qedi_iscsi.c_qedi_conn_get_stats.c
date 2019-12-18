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
typedef  void* uint32_t ;
struct qedi_ctx {int /*<<< orphan*/  cdev; } ;
struct qed_iscsi_stats {scalar_t__ iscsi_rx_r2t_pdu_cnt; scalar_t__ iscsi_rx_data_pdu_cnt; scalar_t__ iscsi_tx_data_pdu_cnt; int /*<<< orphan*/  iscsi_rx_bytes_cnt; int /*<<< orphan*/  iscsi_tx_bytes_cnt; } ;
struct iscsi_stats {int custom_length; TYPE_1__* custom; scalar_t__ timeout_err; scalar_t__ digest_err; int /*<<< orphan*/  tmfrsp_pdus; int /*<<< orphan*/  tmfcmd_pdus; void* r2t_pdus; void* datain_pdus; int /*<<< orphan*/  scsirsp_pdus; void* dataout_pdus; int /*<<< orphan*/  scsicmd_pdus; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; } ;
struct iscsi_conn {int /*<<< orphan*/  eh_abort_cnt; int /*<<< orphan*/  tmfrsp_pdus_cnt; int /*<<< orphan*/  tmfcmd_pdus_cnt; void* r2t_pdus_cnt; void* datain_pdus_cnt; int /*<<< orphan*/  scsirsp_pdus_cnt; void* dataout_pdus_cnt; int /*<<< orphan*/  scsicmd_pdus_cnt; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_stats ) (int /*<<< orphan*/ ,struct qed_iscsi_stats*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_conn_to_session (struct iscsi_cls_conn*) ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_session_to_shost (int /*<<< orphan*/ ) ; 
 TYPE_2__* qedi_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_iscsi_stats*) ; 

__attribute__((used)) static void qedi_conn_get_stats(struct iscsi_cls_conn *cls_conn,
				struct iscsi_stats *stats)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct qed_iscsi_stats iscsi_stats;
	struct Scsi_Host *shost;
	struct qedi_ctx *qedi;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cls_conn));
	qedi = iscsi_host_priv(shost);
	qedi_ops->get_stats(qedi->cdev, &iscsi_stats);

	conn->txdata_octets = iscsi_stats.iscsi_tx_bytes_cnt;
	conn->rxdata_octets = iscsi_stats.iscsi_rx_bytes_cnt;
	conn->dataout_pdus_cnt = (uint32_t)iscsi_stats.iscsi_tx_data_pdu_cnt;
	conn->datain_pdus_cnt = (uint32_t)iscsi_stats.iscsi_rx_data_pdu_cnt;
	conn->r2t_pdus_cnt = (uint32_t)iscsi_stats.iscsi_rx_r2t_pdu_cnt;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->tmfrsp_pdus = conn->tmfrsp_pdus_cnt;
	stats->digest_err = 0;
	stats->timeout_err = 0;
	strcpy(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_abort_cnt;
	stats->custom_length = 1;
}