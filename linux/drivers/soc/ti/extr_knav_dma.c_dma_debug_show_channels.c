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
struct seq_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fdq; int /*<<< orphan*/  thresh; int /*<<< orphan*/  dst_q; int /*<<< orphan*/  desc_type; int /*<<< orphan*/  psinfo_present; int /*<<< orphan*/  einfo_present; } ;
struct TYPE_5__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  filt_pswords; int /*<<< orphan*/  filt_einfo; } ;
struct TYPE_7__ {TYPE_2__ rx; TYPE_1__ tx; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct knav_dma_chan {scalar_t__ direction; TYPE_4__ cfg; } ;

/* Variables and functions */
 scalar_t__ DMA_MEM_TO_DEV ; 
 int KNAV_DMA_FDQ_PER_CHAN ; 
 int /*<<< orphan*/  chan_number (struct knav_dma_chan*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void dma_debug_show_channels(struct seq_file *s,
					struct knav_dma_chan *chan)
{
	int i;

	seq_printf(s, "\t%s %d:\t",
		((chan->direction == DMA_MEM_TO_DEV) ? "tx chan" : "rx flow"),
		chan_number(chan));

	if (chan->direction == DMA_MEM_TO_DEV) {
		seq_printf(s, "einfo - %d, pswords - %d, priority - %d\n",
			chan->cfg.u.tx.filt_einfo,
			chan->cfg.u.tx.filt_pswords,
			chan->cfg.u.tx.priority);
	} else {
		seq_printf(s, "einfo - %d, psinfo - %d, desc_type - %d\n",
			chan->cfg.u.rx.einfo_present,
			chan->cfg.u.rx.psinfo_present,
			chan->cfg.u.rx.desc_type);
		seq_printf(s, "\t\t\tdst_q: [%d], thresh: %d fdq: ",
			chan->cfg.u.rx.dst_q,
			chan->cfg.u.rx.thresh);
		for (i = 0; i < KNAV_DMA_FDQ_PER_CHAN; i++)
			seq_printf(s, "[%d]", chan->cfg.u.rx.fdq[i]);
		seq_printf(s, "\n");
	}
}