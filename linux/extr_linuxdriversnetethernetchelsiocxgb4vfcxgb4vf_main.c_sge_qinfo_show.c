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
struct sge_rspq {char* abs_id; size_t pktcnt_idx; char* cidx; char* gen; int /*<<< orphan*/  iqe_len; int /*<<< orphan*/  size; TYPE_4__* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  cidx; int /*<<< orphan*/  pidx; int /*<<< orphan*/  in_use; int /*<<< orphan*/  size; int /*<<< orphan*/  abs_id; } ;
struct sge_eth_txq {TYPE_3__ q; } ;
struct TYPE_5__ {int /*<<< orphan*/  cidx; int /*<<< orphan*/  pidx; int /*<<< orphan*/  avail; int /*<<< orphan*/  size; int /*<<< orphan*/  abs_id; } ;
struct sge_eth_rxq {TYPE_1__ fl; struct sge_rspq const rspq; } ;
struct seq_file {struct adapter* private; } ;
struct port_info {int port_id; } ;
struct TYPE_6__ {char** counter_val; struct sge_rspq intrq; struct sge_rspq fw_evtq; scalar_t__ ethqsets; struct sge_eth_txq* ethtxq; struct sge_eth_rxq* ethrxq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int /*<<< orphan*/  MIN_FL_RESID ; 
 int QPL ; 
 int min (int,scalar_t__) ; 
 scalar_t__ netdev_priv (TYPE_4__*) ; 
 char* qtimer_val (struct adapter*,struct sge_rspq const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int sge_qinfo_show(struct seq_file *seq, void *v)
{
	struct adapter *adapter = seq->private;
	int eth_entries = DIV_ROUND_UP(adapter->sge.ethqsets, QPL);
	int qs, r = (uintptr_t)v - 1;

	if (r)
		seq_putc(seq, '\n');

	#define S3(fmt_spec, s, v) \
		do {\
			seq_printf(seq, "%-12s", s); \
			for (qs = 0; qs < n; ++qs) \
				seq_printf(seq, " %16" fmt_spec, v); \
			seq_putc(seq, '\n'); \
		} while (0)
	#define S(s, v)		S3("s", s, v)
	#define T(s, v)		S3("u", s, txq[qs].v)
	#define R(s, v)		S3("u", s, rxq[qs].v)

	if (r < eth_entries) {
		const struct sge_eth_rxq *rxq = &adapter->sge.ethrxq[r * QPL];
		const struct sge_eth_txq *txq = &adapter->sge.ethtxq[r * QPL];
		int n = min(QPL, adapter->sge.ethqsets - QPL * r);

		S("QType:", "Ethernet");
		S("Interface:",
		  (rxq[qs].rspq.netdev
		   ? rxq[qs].rspq.netdev->name
		   : "N/A"));
		S3("d", "Port:",
		   (rxq[qs].rspq.netdev
		    ? ((struct port_info *)
		       netdev_priv(rxq[qs].rspq.netdev))->port_id
		    : -1));
		T("TxQ ID:", q.abs_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ PIdx:", q.pidx);
		T("TxQ CIdx:", q.cidx);
		R("RspQ ID:", rspq.abs_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		S3("u", "Intr delay:", qtimer_val(adapter, &rxq[qs].rspq));
		S3("u", "Intr pktcnt:",
		   adapter->sge.counter_val[rxq[qs].rspq.pktcnt_idx]);
		R("RspQ CIdx:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		R("FL ID:", fl.abs_id);
		R("FL size:", fl.size - MIN_FL_RESID);
		R("FL avail:", fl.avail);
		R("FL PIdx:", fl.pidx);
		R("FL CIdx:", fl.cidx);
		return 0;
	}

	r -= eth_entries;
	if (r == 0) {
		const struct sge_rspq *evtq = &adapter->sge.fw_evtq;

		seq_printf(seq, "%-12s %16s\n", "QType:", "FW event queue");
		seq_printf(seq, "%-12s %16u\n", "RspQ ID:", evtq->abs_id);
		seq_printf(seq, "%-12s %16u\n", "Intr delay:",
			   qtimer_val(adapter, evtq));
		seq_printf(seq, "%-12s %16u\n", "Intr pktcnt:",
			   adapter->sge.counter_val[evtq->pktcnt_idx]);
		seq_printf(seq, "%-12s %16u\n", "RspQ Cidx:", evtq->cidx);
		seq_printf(seq, "%-12s %16u\n", "RspQ Gen:", evtq->gen);
	} else if (r == 1) {
		const struct sge_rspq *intrq = &adapter->sge.intrq;

		seq_printf(seq, "%-12s %16s\n", "QType:", "Interrupt Queue");
		seq_printf(seq, "%-12s %16u\n", "RspQ ID:", intrq->abs_id);
		seq_printf(seq, "%-12s %16u\n", "Intr delay:",
			   qtimer_val(adapter, intrq));
		seq_printf(seq, "%-12s %16u\n", "Intr pktcnt:",
			   adapter->sge.counter_val[intrq->pktcnt_idx]);
		seq_printf(seq, "%-12s %16u\n", "RspQ Cidx:", intrq->cidx);
		seq_printf(seq, "%-12s %16u\n", "RspQ Gen:", intrq->gen);
	}

	#undef R
	#undef T
	#undef S
	#undef S3

	return 0;
}