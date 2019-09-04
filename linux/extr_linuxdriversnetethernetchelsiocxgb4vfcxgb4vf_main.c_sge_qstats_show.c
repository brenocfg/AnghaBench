#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sge_rspq {char* unhandled_irqs; char* cidx; char* gen; } ;
struct TYPE_7__ {int /*<<< orphan*/  restarts; int /*<<< orphan*/  stops; } ;
struct sge_eth_txq {int /*<<< orphan*/  mapping_err; TYPE_1__ q; int /*<<< orphan*/  vlan_ins; int /*<<< orphan*/  tx_cso; int /*<<< orphan*/  tso; } ;
struct TYPE_8__ {int /*<<< orphan*/  starving; int /*<<< orphan*/  large_alloc_failed; int /*<<< orphan*/  alloc_failed; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  lro_pkts; int /*<<< orphan*/  lro_merged; int /*<<< orphan*/  vlan_ex; int /*<<< orphan*/  rx_cso; int /*<<< orphan*/  pkts; } ;
struct TYPE_11__ {int /*<<< orphan*/  unhandled_irqs; TYPE_4__* netdev; } ;
struct sge_eth_rxq {TYPE_2__ fl; TYPE_6__ stats; TYPE_5__ rspq; } ;
struct seq_file {struct adapter* private; } ;
struct TYPE_9__ {struct sge_rspq intrq; struct sge_rspq fw_evtq; scalar_t__ ethqsets; struct sge_eth_txq* ethtxq; struct sge_eth_rxq* ethrxq; } ;
struct adapter {TYPE_3__ sge; } ;
struct TYPE_10__ {char* name; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int QPL ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int sge_qstats_show(struct seq_file *seq, void *v)
{
	struct adapter *adapter = seq->private;
	int eth_entries = DIV_ROUND_UP(adapter->sge.ethqsets, QPL);
	int qs, r = (uintptr_t)v - 1;

	if (r)
		seq_putc(seq, '\n');

	#define S3(fmt, s, v) \
		do { \
			seq_printf(seq, "%-16s", s); \
			for (qs = 0; qs < n; ++qs) \
				seq_printf(seq, " %8" fmt, v); \
			seq_putc(seq, '\n'); \
		} while (0)
	#define S(s, v)		S3("s", s, v)

	#define T3(fmt, s, v)	S3(fmt, s, txq[qs].v)
	#define T(s, v)		T3("lu", s, v)

	#define R3(fmt, s, v)	S3(fmt, s, rxq[qs].v)
	#define R(s, v)		R3("lu", s, v)

	if (r < eth_entries) {
		const struct sge_eth_rxq *rxq = &adapter->sge.ethrxq[r * QPL];
		const struct sge_eth_txq *txq = &adapter->sge.ethtxq[r * QPL];
		int n = min(QPL, adapter->sge.ethqsets - QPL * r);

		S("QType:", "Ethernet");
		S("Interface:",
		  (rxq[qs].rspq.netdev
		   ? rxq[qs].rspq.netdev->name
		   : "N/A"));
		R3("u", "RspQNullInts:", rspq.unhandled_irqs);
		R("RxPackets:", stats.pkts);
		R("RxCSO:", stats.rx_cso);
		R("VLANxtract:", stats.vlan_ex);
		R("LROmerged:", stats.lro_merged);
		R("LROpackets:", stats.lro_pkts);
		R("RxDrops:", stats.rx_drops);
		T("TSO:", tso);
		T("TxCSO:", tx_cso);
		T("VLANins:", vlan_ins);
		T("TxQFull:", q.stops);
		T("TxQRestarts:", q.restarts);
		T("TxMapErr:", mapping_err);
		R("FLAllocErr:", fl.alloc_failed);
		R("FLLrgAlcErr:", fl.large_alloc_failed);
		R("FLStarving:", fl.starving);
		return 0;
	}

	r -= eth_entries;
	if (r == 0) {
		const struct sge_rspq *evtq = &adapter->sge.fw_evtq;

		seq_printf(seq, "%-8s %16s\n", "QType:", "FW event queue");
		seq_printf(seq, "%-16s %8u\n", "RspQNullInts:",
			   evtq->unhandled_irqs);
		seq_printf(seq, "%-16s %8u\n", "RspQ CIdx:", evtq->cidx);
		seq_printf(seq, "%-16s %8u\n", "RspQ Gen:", evtq->gen);
	} else if (r == 1) {
		const struct sge_rspq *intrq = &adapter->sge.intrq;

		seq_printf(seq, "%-8s %16s\n", "QType:", "Interrupt Queue");
		seq_printf(seq, "%-16s %8u\n", "RspQNullInts:",
			   intrq->unhandled_irqs);
		seq_printf(seq, "%-16s %8u\n", "RspQ CIdx:", intrq->cidx);
		seq_printf(seq, "%-16s %8u\n", "RspQ Gen:", intrq->gen);
	}

	#undef R
	#undef T
	#undef S
	#undef R3
	#undef T3
	#undef S3

	return 0;
}