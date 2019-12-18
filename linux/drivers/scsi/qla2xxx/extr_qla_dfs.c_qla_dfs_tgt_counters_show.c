#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t u16 ;
struct seq_file {struct scsi_qla_host* private; } ;
struct TYPE_7__ {scalar_t__ dif_app_tag_err; scalar_t__ dif_ref_tag_err; scalar_t__ dif_guard_err; scalar_t__ dif_output_requests; scalar_t__ dif_input_requests; scalar_t__ dif_output_bytes; scalar_t__ dif_input_bytes; } ;
struct TYPE_8__ {TYPE_3__ qla_dif_stats; } ;
struct scsi_qla_host {TYPE_4__ qla_stats; TYPE_1__* hw; } ;
struct TYPE_6__ {scalar_t__ num_term_xchg_sent; scalar_t__ num_alloc_iocb_failed; scalar_t__ num_q_full_sent; scalar_t__ core_qla_free_cmd; scalar_t__ qla_core_ret_sta_ctio; scalar_t__ core_qla_snd_status; scalar_t__ qla_core_ret_ctio; scalar_t__ core_qla_que_buf; scalar_t__ qla_core_sbt_cmd; } ;
struct qla_qpair {TYPE_2__ tgt_counters; } ;
struct TYPE_5__ {size_t max_qpairs; struct qla_qpair** queue_pair_map; struct qla_qpair* base_qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
qla_dfs_tgt_counters_show(struct seq_file *s, void *unused)
{
	struct scsi_qla_host *vha = s->private;
	struct qla_qpair *qpair = vha->hw->base_qpair;
	uint64_t qla_core_sbt_cmd, core_qla_que_buf, qla_core_ret_ctio,
		core_qla_snd_status, qla_core_ret_sta_ctio, core_qla_free_cmd,
		num_q_full_sent, num_alloc_iocb_failed, num_term_xchg_sent;
	u16 i;

	qla_core_sbt_cmd = qpair->tgt_counters.qla_core_sbt_cmd;
	core_qla_que_buf = qpair->tgt_counters.core_qla_que_buf;
	qla_core_ret_ctio = qpair->tgt_counters.qla_core_ret_ctio;
	core_qla_snd_status = qpair->tgt_counters.core_qla_snd_status;
	qla_core_ret_sta_ctio = qpair->tgt_counters.qla_core_ret_sta_ctio;
	core_qla_free_cmd = qpair->tgt_counters.core_qla_free_cmd;
	num_q_full_sent = qpair->tgt_counters.num_q_full_sent;
	num_alloc_iocb_failed = qpair->tgt_counters.num_alloc_iocb_failed;
	num_term_xchg_sent = qpair->tgt_counters.num_term_xchg_sent;

	for (i = 0; i < vha->hw->max_qpairs; i++) {
		qpair = vha->hw->queue_pair_map[i];
		if (!qpair)
			continue;
		qla_core_sbt_cmd += qpair->tgt_counters.qla_core_sbt_cmd;
		core_qla_que_buf += qpair->tgt_counters.core_qla_que_buf;
		qla_core_ret_ctio += qpair->tgt_counters.qla_core_ret_ctio;
		core_qla_snd_status += qpair->tgt_counters.core_qla_snd_status;
		qla_core_ret_sta_ctio +=
		    qpair->tgt_counters.qla_core_ret_sta_ctio;
		core_qla_free_cmd += qpair->tgt_counters.core_qla_free_cmd;
		num_q_full_sent += qpair->tgt_counters.num_q_full_sent;
		num_alloc_iocb_failed +=
		    qpair->tgt_counters.num_alloc_iocb_failed;
		num_term_xchg_sent += qpair->tgt_counters.num_term_xchg_sent;
	}

	seq_puts(s, "Target Counters\n");
	seq_printf(s, "qla_core_sbt_cmd = %lld\n",
		qla_core_sbt_cmd);
	seq_printf(s, "qla_core_ret_sta_ctio = %lld\n",
		qla_core_ret_sta_ctio);
	seq_printf(s, "qla_core_ret_ctio = %lld\n",
		qla_core_ret_ctio);
	seq_printf(s, "core_qla_que_buf = %lld\n",
		core_qla_que_buf);
	seq_printf(s, "core_qla_snd_status = %lld\n",
		core_qla_snd_status);
	seq_printf(s, "core_qla_free_cmd = %lld\n",
		core_qla_free_cmd);
	seq_printf(s, "num alloc iocb failed = %lld\n",
		num_alloc_iocb_failed);
	seq_printf(s, "num term exchange sent = %lld\n",
		num_term_xchg_sent);
	seq_printf(s, "num Q full sent = %lld\n",
		num_q_full_sent);

	/* DIF stats */
	seq_printf(s, "DIF Inp Bytes = %lld\n",
		vha->qla_stats.qla_dif_stats.dif_input_bytes);
	seq_printf(s, "DIF Outp Bytes = %lld\n",
		vha->qla_stats.qla_dif_stats.dif_output_bytes);
	seq_printf(s, "DIF Inp Req = %lld\n",
		vha->qla_stats.qla_dif_stats.dif_input_requests);
	seq_printf(s, "DIF Outp Req = %lld\n",
		vha->qla_stats.qla_dif_stats.dif_output_requests);
	seq_printf(s, "DIF Guard err = %d\n",
		vha->qla_stats.qla_dif_stats.dif_guard_err);
	seq_printf(s, "DIF Ref tag err = %d\n",
		vha->qla_stats.qla_dif_stats.dif_ref_tag_err);
	seq_printf(s, "DIF App tag err = %d\n",
		vha->qla_stats.qla_dif_stats.dif_app_tag_err);
	return 0;
}