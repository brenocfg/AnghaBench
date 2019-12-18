#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_11__ {int /*<<< orphan*/  buff_id; } ;
struct wil_rx_enhanced_desc {TYPE_4__ mac; } ;
struct wil_ring {int size; TYPE_7__* ctx; TYPE_3__* va; } ;
struct TYPE_13__ {TYPE_5__* buff_arr; int /*<<< orphan*/  size; } ;
struct wil6210_priv {TYPE_6__ rx_buff_mgmt; scalar_t__ use_enhanced_dma_hw; struct wil_ring ring_rx; struct wil_ring* ring_tx; } ;
struct vring_tx_desc {int dummy; } ;
struct sk_buff {int dummy; } ;
struct seq_file {struct wil6210_priv* private; } ;
struct TYPE_14__ {struct sk_buff* skb; } ;
struct TYPE_12__ {struct sk_buff* skb; } ;
struct TYPE_9__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_8__ {struct vring_tx_desc legacy; } ;
struct TYPE_10__ {TYPE_2__ rx; TYPE_1__ tx; } ;

/* Variables and functions */
 int WIL6210_MAX_TX_RINGS ; 
 int dbg_ring_index ; 
 int dbg_txdesc_index ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  wil_seq_print_skb (struct seq_file*,struct sk_buff*) ; 
 int /*<<< orphan*/  wil_val_in_range (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txdesc_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	struct wil_ring *ring;
	bool tx;
	int ring_idx = dbg_ring_index;
	int txdesc_idx = dbg_txdesc_index;
	volatile struct vring_tx_desc *d;
	volatile u32 *u;
	struct sk_buff *skb;

	if (wil->use_enhanced_dma_hw) {
		/* RX ring index == 0 */
		if (ring_idx >= WIL6210_MAX_TX_RINGS) {
			seq_printf(s, "invalid ring index %d\n", ring_idx);
			return 0;
		}
		tx = ring_idx > 0; /* desc ring 0 is reserved for RX */
	} else {
		/* RX ring index == WIL6210_MAX_TX_RINGS */
		if (ring_idx > WIL6210_MAX_TX_RINGS) {
			seq_printf(s, "invalid ring index %d\n", ring_idx);
			return 0;
		}
		tx = (ring_idx < WIL6210_MAX_TX_RINGS);
	}

	ring = tx ? &wil->ring_tx[ring_idx] : &wil->ring_rx;

	if (!ring->va) {
		if (tx)
			seq_printf(s, "No Tx[%2d] RING\n", ring_idx);
		else
			seq_puts(s, "No Rx RING\n");
		return 0;
	}

	if (txdesc_idx >= ring->size) {
		if (tx)
			seq_printf(s, "[%2d] TxDesc index (%d) >= size (%d)\n",
				   ring_idx, txdesc_idx, ring->size);
		else
			seq_printf(s, "RxDesc index (%d) >= size (%d)\n",
				   txdesc_idx, ring->size);
		return 0;
	}

	/* use struct vring_tx_desc for Rx as well,
	 * only field used, .dma.length, is the same
	 */
	d = &ring->va[txdesc_idx].tx.legacy;
	u = (volatile u32 *)d;
	skb = NULL;

	if (wil->use_enhanced_dma_hw) {
		if (tx) {
			skb = ring->ctx ? ring->ctx[txdesc_idx].skb : NULL;
		} else if (wil->rx_buff_mgmt.buff_arr) {
			struct wil_rx_enhanced_desc *rx_d =
				(struct wil_rx_enhanced_desc *)
				&ring->va[txdesc_idx].rx.enhanced;
			u16 buff_id = le16_to_cpu(rx_d->mac.buff_id);

			if (!wil_val_in_range(buff_id, 0,
					      wil->rx_buff_mgmt.size))
				seq_printf(s, "invalid buff_id %d\n", buff_id);
			else
				skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
		}
	} else {
		skb = ring->ctx[txdesc_idx].skb;
	}
	if (tx)
		seq_printf(s, "Tx[%2d][%3d] = {\n", ring_idx,
			   txdesc_idx);
	else
		seq_printf(s, "Rx[%3d] = {\n", txdesc_idx);
	seq_printf(s, "  MAC = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	seq_printf(s, "  DMA = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[4], u[5], u[6], u[7]);
	seq_printf(s, "  SKB = 0x%p\n", skb);

	if (skb) {
		skb_get(skb);
		wil_seq_print_skb(s, skb);
		kfree_skb(skb);
	}
	seq_puts(s, "}\n");

	return 0;
}