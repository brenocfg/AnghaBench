#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wil_ring_tx_data {scalar_t__ mid; int /*<<< orphan*/  dot1x_open; int /*<<< orphan*/  enabled; } ;
struct wil_ring {int /*<<< orphan*/  va; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {scalar_t__** ring2cid_tid; scalar_t__ max_assoc_sta; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAE ; 
 int WIL6210_MAX_TX_RINGS ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,...) ; 
 int wil_get_min_tx_ring_id (struct wil6210_priv*) ; 

__attribute__((used)) static struct wil_ring *wil_find_tx_ring_sta(struct wil6210_priv *wil,
					     struct wil6210_vif *vif,
					     struct sk_buff *skb)
{
	struct wil_ring *ring;
	int i;
	u8 cid;
	struct wil_ring_tx_data  *txdata;
	int min_ring_id = wil_get_min_tx_ring_id(wil);

	/* In the STA mode, it is expected to have only 1 VRING
	 * for the AP we connected to.
	 * find 1-st vring eligible for this skb and use it.
	 */
	for (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) {
		ring = &wil->ring_tx[i];
		txdata = &wil->ring_tx_data[i];
		if (!ring->va || !txdata->enabled || txdata->mid != vif->mid)
			continue;

		cid = wil->ring2cid_tid[i][0];
		if (cid >= wil->max_assoc_sta) /* skip BCAST */
			continue;

		if (!wil->ring_tx_data[i].dot1x_open &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			continue;

		wil_dbg_txrx(wil, "Tx -> ring %d\n", i);

		return ring;
	}

	wil_dbg_txrx(wil, "Tx while no rings active?\n");

	return NULL;
}