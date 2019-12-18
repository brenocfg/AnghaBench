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
typedef  size_t u8 ;
struct wil_ring_tx_data {scalar_t__ mid; int /*<<< orphan*/  dot1x_open; int /*<<< orphan*/  enabled; } ;
struct wil_ring {int /*<<< orphan*/  va; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {size_t** ring2cid_tid; size_t max_assoc_sta; TYPE_1__* sta; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int WIL6210_MAX_TX_RINGS ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,size_t const*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int wil_get_min_tx_ring_id (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_set_da_for_vring (struct wil6210_priv*,struct sk_buff*,int) ; 
 size_t* wil_skb_get_sa (struct sk_buff*) ; 
 int /*<<< orphan*/  wil_tx_ring (struct wil6210_priv*,struct wil6210_vif*,struct wil_ring*,struct sk_buff*) ; 

__attribute__((used)) static struct wil_ring *wil_find_tx_bcast_2(struct wil6210_priv *wil,
					    struct wil6210_vif *vif,
					    struct sk_buff *skb)
{
	struct wil_ring *v, *v2;
	struct sk_buff *skb2;
	int i;
	u8 cid;
	const u8 *src = wil_skb_get_sa(skb);
	struct wil_ring_tx_data *txdata, *txdata2;
	int min_ring_id = wil_get_min_tx_ring_id(wil);

	/* find 1-st vring eligible for data */
	for (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) {
		v = &wil->ring_tx[i];
		txdata = &wil->ring_tx_data[i];
		if (!v->va || !txdata->enabled || txdata->mid != vif->mid)
			continue;

		cid = wil->ring2cid_tid[i][0];
		if (cid >= wil->max_assoc_sta) /* skip BCAST */
			continue;
		if (!wil->ring_tx_data[i].dot1x_open &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			continue;

		/* don't Tx back to source when re-routing Rx->Tx at the AP */
		if (0 == memcmp(wil->sta[cid].addr, src, ETH_ALEN))
			continue;

		goto found;
	}

	wil_dbg_txrx(wil, "Tx while no vrings active?\n");

	return NULL;

found:
	wil_dbg_txrx(wil, "BCAST -> ring %d\n", i);
	wil_set_da_for_vring(wil, skb, i);

	/* find other active vrings and duplicate skb for each */
	for (i++; i < WIL6210_MAX_TX_RINGS; i++) {
		v2 = &wil->ring_tx[i];
		txdata2 = &wil->ring_tx_data[i];
		if (!v2->va || txdata2->mid != vif->mid)
			continue;
		cid = wil->ring2cid_tid[i][0];
		if (cid >= wil->max_assoc_sta) /* skip BCAST */
			continue;
		if (!wil->ring_tx_data[i].dot1x_open &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			continue;

		if (0 == memcmp(wil->sta[cid].addr, src, ETH_ALEN))
			continue;

		skb2 = skb_copy(skb, GFP_ATOMIC);
		if (skb2) {
			wil_dbg_txrx(wil, "BCAST DUP -> ring %d\n", i);
			wil_set_da_for_vring(wil, skb2, i);
			wil_tx_ring(wil, vif, v2, skb2);
			/* successful call to wil_tx_ring takes skb2 ref */
			dev_kfree_skb_any(skb2);
		} else {
			wil_err(wil, "skb_copy failed\n");
		}
	}

	return v;
}