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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; struct gve_rx_desc* desc_ring; } ;
struct gve_rx_ring {int cnt; int mask; int rpackets; int fill_cnt; int /*<<< orphan*/  statss; int /*<<< orphan*/  rbytes; TYPE_1__ desc; int /*<<< orphan*/  q_num; struct gve_priv* gve; } ;
struct gve_rx_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  flags_seq; } ;
struct gve_priv {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 scalar_t__ GVE_RX_PAD ; 
 int /*<<< orphan*/  GVE_SEQNO (int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  gve_next_seqno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_rx (struct gve_rx_ring*,struct gve_rx_desc*,int /*<<< orphan*/ ,int) ; 
 int gve_rx_work_pending (struct gve_rx_ring*) ; 
 int /*<<< orphan*/  gve_rx_write_doorbell (struct gve_priv*,struct gve_rx_ring*) ; 
 int /*<<< orphan*/  gve_schedule_reset (struct gve_priv*) ; 
 int /*<<< orphan*/  netif_info (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,struct gve_rx_desc*,...) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

bool gve_clean_rx_done(struct gve_rx_ring *rx, int budget,
		       netdev_features_t feat)
{
	struct gve_priv *priv = rx->gve;
	struct gve_rx_desc *desc;
	u32 cnt = rx->cnt;
	u32 idx = cnt & rx->mask;
	u32 work_done = 0;
	u64 bytes = 0;

	desc = rx->desc.desc_ring + idx;
	while ((GVE_SEQNO(desc->flags_seq) == rx->desc.seqno) &&
	       work_done < budget) {
		netif_info(priv, rx_status, priv->dev,
			   "[%d] idx=%d desc=%p desc->flags_seq=0x%x\n",
			   rx->q_num, idx, desc, desc->flags_seq);
		netif_info(priv, rx_status, priv->dev,
			   "[%d] seqno=%d rx->desc.seqno=%d\n",
			   rx->q_num, GVE_SEQNO(desc->flags_seq),
			   rx->desc.seqno);
		bytes += be16_to_cpu(desc->len) - GVE_RX_PAD;
		if (!gve_rx(rx, desc, feat, idx))
			gve_schedule_reset(priv);
		cnt++;
		idx = cnt & rx->mask;
		desc = rx->desc.desc_ring + idx;
		rx->desc.seqno = gve_next_seqno(rx->desc.seqno);
		work_done++;
	}

	if (!work_done)
		return false;

	u64_stats_update_begin(&rx->statss);
	rx->rpackets += work_done;
	rx->rbytes += bytes;
	u64_stats_update_end(&rx->statss);
	rx->cnt = cnt;
	rx->fill_cnt += work_done;

	/* restock desc ring slots */
	dma_wmb();	/* Ensure descs are visible before ringing doorbell */
	gve_rx_write_doorbell(priv, rx);
	return gve_rx_work_pending(rx);
}