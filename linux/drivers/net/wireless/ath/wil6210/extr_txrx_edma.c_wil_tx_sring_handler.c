#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union wil_tx_desc {int dummy; } wil_tx_desc ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
struct wil_tx_enhanced_desc {TYPE_3__ dma; } ;
struct wil_status_ring {scalar_t__ desc_rdy_pol; int swhead; int size; int /*<<< orphan*/  hwtail; } ;
struct wil_ring_tx_status {unsigned int num_descriptors; unsigned int ring_id; scalar_t__ status; } ;
struct wil_ring_tx_data {size_t mid; int /*<<< orphan*/  last_idle; int /*<<< orphan*/  enabled; } ;
struct wil_ring {size_t swtail; TYPE_2__* va; struct wil_ctx* ctx; } ;
struct wil_net_stats {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct wil_ctx {struct sk_buff* skb; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int** ring2cid_tid; int max_assoc_sta; int /*<<< orphan*/  ring_idle_trsh; TYPE_5__* sta; struct wil6210_vif** vifs; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ len; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_4__ stats; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_10__ {struct wil_net_stats stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 unsigned int WIL6210_MAX_TX_RINGS ; 
 unsigned int WIL_EDMA_TX_SRING_UPDATE_HW_TAIL ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cycles () ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct wil_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_wil6210_tx_status (struct wil_ring_tx_status*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_consume_skb (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_get_next_tx_status_msg (struct wil_status_ring*,scalar_t__*,struct wil_ring_tx_status*) ; 
 int /*<<< orphan*/  wil_hex_dump_txrx (char*,int /*<<< orphan*/ ,int,int,void const*,int,int) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,unsigned int) ; 
 size_t wil_ring_next_tail (struct wil_ring*) ; 
 int wil_ring_used_tx (struct wil_ring*) ; 
 int /*<<< orphan*/  wil_sring_advance_swhead (struct wil_status_ring*) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_tx_complete_handle_eapol (struct wil6210_vif*,struct sk_buff*) ; 
 int /*<<< orphan*/  wil_tx_desc_unmap_edma (struct device*,union wil_tx_desc*,struct wil_ctx*) ; 
 int /*<<< orphan*/  wil_tx_latency_calc (struct wil6210_priv*,struct sk_buff*,TYPE_5__*) ; 
 int /*<<< orphan*/  wil_update_net_queues (struct wil6210_priv*,struct wil6210_vif*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wil_val_in_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

int wil_tx_sring_handler(struct wil6210_priv *wil,
			 struct wil_status_ring *sring)
{
	struct net_device *ndev;
	struct device *dev = wil_to_dev(wil);
	struct wil_ring *ring = NULL;
	struct wil_ring_tx_data *txdata;
	/* Total number of completed descriptors in all descriptor rings */
	int desc_cnt = 0;
	int cid;
	struct wil_net_stats *stats;
	struct wil_tx_enhanced_desc *_d;
	unsigned int ring_id;
	unsigned int num_descs, num_statuses = 0;
	int i;
	u8 dr_bit; /* Descriptor Ready bit */
	struct wil_ring_tx_status msg;
	struct wil6210_vif *vif;
	int used_before_complete;
	int used_new;

	wil_get_next_tx_status_msg(sring, &dr_bit, &msg);

	/* Process completion messages while DR bit has the expected polarity */
	while (dr_bit == sring->desc_rdy_pol) {
		num_descs = msg.num_descriptors;
		if (!num_descs) {
			wil_err(wil, "invalid num_descs 0\n");
			goto again;
		}

		/* Find the corresponding descriptor ring */
		ring_id = msg.ring_id;

		if (unlikely(ring_id >= WIL6210_MAX_TX_RINGS)) {
			wil_err(wil, "invalid ring id %d\n", ring_id);
			goto again;
		}
		ring = &wil->ring_tx[ring_id];
		if (unlikely(!ring->va)) {
			wil_err(wil, "Tx irq[%d]: ring not initialized\n",
				ring_id);
			goto again;
		}
		txdata = &wil->ring_tx_data[ring_id];
		if (unlikely(!txdata->enabled)) {
			wil_info(wil, "Tx irq[%d]: ring disabled\n", ring_id);
			goto again;
		}
		vif = wil->vifs[txdata->mid];
		if (unlikely(!vif)) {
			wil_dbg_txrx(wil, "invalid MID %d for ring %d\n",
				     txdata->mid, ring_id);
			goto again;
		}

		ndev = vif_to_ndev(vif);

		cid = wil->ring2cid_tid[ring_id][0];
		stats = (cid < wil->max_assoc_sta) ? &wil->sta[cid].stats :
						     NULL;

		wil_dbg_txrx(wil,
			     "tx_status: completed desc_ring (%d), num_descs (%d)\n",
			     ring_id, num_descs);

		used_before_complete = wil_ring_used_tx(ring);

		for (i = 0 ; i < num_descs; ++i) {
			struct wil_ctx *ctx = &ring->ctx[ring->swtail];
			struct wil_tx_enhanced_desc dd, *d = &dd;
			u16 dmalen;
			struct sk_buff *skb = ctx->skb;

			_d = (struct wil_tx_enhanced_desc *)
				&ring->va[ring->swtail].tx.enhanced;
			*d = *_d;

			dmalen = le16_to_cpu(d->dma.length);
			trace_wil6210_tx_status(&msg, ring->swtail, dmalen);
			wil_dbg_txrx(wil,
				     "TxC[%2d][%3d] : %d bytes, status 0x%02x\n",
				     ring_id, ring->swtail, dmalen,
				     msg.status);
			wil_hex_dump_txrx("TxS ", DUMP_PREFIX_NONE, 32, 4,
					  (const void *)&msg, sizeof(msg),
					  false);

			wil_tx_desc_unmap_edma(dev,
					       (union wil_tx_desc *)d,
					       ctx);

			if (skb) {
				if (likely(msg.status == 0)) {
					ndev->stats.tx_packets++;
					ndev->stats.tx_bytes += skb->len;
					if (stats) {
						stats->tx_packets++;
						stats->tx_bytes += skb->len;

						wil_tx_latency_calc(wil, skb,
							&wil->sta[cid]);
					}
				} else {
					ndev->stats.tx_errors++;
					if (stats)
						stats->tx_errors++;
				}

				if (skb->protocol == cpu_to_be16(ETH_P_PAE))
					wil_tx_complete_handle_eapol(vif, skb);

				wil_consume_skb(skb, msg.status == 0);
			}
			memset(ctx, 0, sizeof(*ctx));
			/* Make sure the ctx is zeroed before updating the tail
			 * to prevent a case where wil_tx_ring will see
			 * this descriptor as used and handle it before ctx zero
			 * is completed.
			 */
			wmb();

			ring->swtail = wil_ring_next_tail(ring);

			desc_cnt++;
		}

		/* performance monitoring */
		used_new = wil_ring_used_tx(ring);
		if (wil_val_in_range(wil->ring_idle_trsh,
				     used_new, used_before_complete)) {
			wil_dbg_txrx(wil, "Ring[%2d] idle %d -> %d\n",
				     ring_id, used_before_complete, used_new);
			txdata->last_idle = get_cycles();
		}

again:
		num_statuses++;
		if (num_statuses % WIL_EDMA_TX_SRING_UPDATE_HW_TAIL == 0)
			/* update HW tail to allow HW to push new statuses */
			wil_w(wil, sring->hwtail, sring->swhead);

		wil_sring_advance_swhead(sring);

		wil_get_next_tx_status_msg(sring, &dr_bit, &msg);
	}

	/* shall we wake net queues? */
	if (desc_cnt)
		wil_update_net_queues(wil, vif, NULL, false);

	if (num_statuses % WIL_EDMA_TX_SRING_UPDATE_HW_TAIL != 0)
		/* Update the HW tail ptr (RD ptr) */
		wil_w(wil, sring->hwtail, (sring->swhead - 1) % sring->size);

	return desc_cnt;
}