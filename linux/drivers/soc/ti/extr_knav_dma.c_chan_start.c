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
typedef  int u32 ;
struct knav_dma_chan {scalar_t__ direction; int /*<<< orphan*/  lock; int /*<<< orphan*/  cfg; TYPE_6__* reg_rx_flow; TYPE_3__* reg_tx_sched; TYPE_1__* reg_chan; } ;
struct TYPE_10__ {scalar_t__ err_mode; int desc_type; int sop_offset; int dst_q; int* fdq; scalar_t__ psinfo_at_sop; scalar_t__ psinfo_present; scalar_t__ einfo_present; } ;
struct TYPE_8__ {int priority; scalar_t__ filt_einfo; scalar_t__ filt_pswords; } ;
struct TYPE_11__ {TYPE_4__ rx; TYPE_2__ tx; } ;
struct knav_dma_cfg {TYPE_5__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/ * thresh; int /*<<< orphan*/ * fdq_sel; int /*<<< orphan*/  tag_sel; int /*<<< orphan*/  tags; int /*<<< orphan*/  control; } ;
struct TYPE_9__ {int /*<<< orphan*/  prio; } ;
struct TYPE_7__ {int /*<<< orphan*/  control; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int CHAN_ERR_RETRY ; 
 int CHAN_HAS_EPIB ; 
 int CHAN_HAS_PSINFO ; 
 int CHAN_PSINFO_AT_SOP ; 
 int CHAN_QNUM_MASK ; 
 int CHAN_SOP_OFF_MASK ; 
 int CHAN_SOP_OFF_SHIFT ; 
 int DESC_TYPE_MASK ; 
 int DESC_TYPE_SHIFT ; 
 int DMA_ENABLE ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ DMA_RETRY ; 
 int DMA_TX_FILT_EINFO ; 
 int DMA_TX_FILT_PSWORDS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct knav_dma_cfg*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chan_start(struct knav_dma_chan *chan,
			struct knav_dma_cfg *cfg)
{
	u32 v = 0;

	spin_lock(&chan->lock);
	if ((chan->direction == DMA_MEM_TO_DEV) && chan->reg_chan) {
		if (cfg->u.tx.filt_pswords)
			v |= DMA_TX_FILT_PSWORDS;
		if (cfg->u.tx.filt_einfo)
			v |= DMA_TX_FILT_EINFO;
		writel_relaxed(v, &chan->reg_chan->mode);
		writel_relaxed(DMA_ENABLE, &chan->reg_chan->control);
	}

	if (chan->reg_tx_sched)
		writel_relaxed(cfg->u.tx.priority, &chan->reg_tx_sched->prio);

	if (chan->reg_rx_flow) {
		v = 0;

		if (cfg->u.rx.einfo_present)
			v |= CHAN_HAS_EPIB;
		if (cfg->u.rx.psinfo_present)
			v |= CHAN_HAS_PSINFO;
		if (cfg->u.rx.err_mode == DMA_RETRY)
			v |= CHAN_ERR_RETRY;
		v |= (cfg->u.rx.desc_type & DESC_TYPE_MASK) << DESC_TYPE_SHIFT;
		if (cfg->u.rx.psinfo_at_sop)
			v |= CHAN_PSINFO_AT_SOP;
		v |= (cfg->u.rx.sop_offset & CHAN_SOP_OFF_MASK)
			<< CHAN_SOP_OFF_SHIFT;
		v |= cfg->u.rx.dst_q & CHAN_QNUM_MASK;

		writel_relaxed(v, &chan->reg_rx_flow->control);
		writel_relaxed(0, &chan->reg_rx_flow->tags);
		writel_relaxed(0, &chan->reg_rx_flow->tag_sel);

		v =  cfg->u.rx.fdq[0] << 16;
		v |=  cfg->u.rx.fdq[1] & CHAN_QNUM_MASK;
		writel_relaxed(v, &chan->reg_rx_flow->fdq_sel[0]);

		v =  cfg->u.rx.fdq[2] << 16;
		v |=  cfg->u.rx.fdq[3] & CHAN_QNUM_MASK;
		writel_relaxed(v, &chan->reg_rx_flow->fdq_sel[1]);

		writel_relaxed(0, &chan->reg_rx_flow->thresh[0]);
		writel_relaxed(0, &chan->reg_rx_flow->thresh[1]);
		writel_relaxed(0, &chan->reg_rx_flow->thresh[2]);
	}

	/* Keep a copy of the cfg */
	memcpy(&chan->cfg, cfg, sizeof(*cfg));
	spin_unlock(&chan->lock);

	return 0;
}