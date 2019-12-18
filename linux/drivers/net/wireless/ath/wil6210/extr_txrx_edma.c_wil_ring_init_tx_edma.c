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
struct wil_ring_tx_data {int dot1x_open; int /*<<< orphan*/  lock; scalar_t__ enabled; } ;
struct wil_ring {int size; } ;
struct wil6210_vif {int /*<<< orphan*/  privacy; } ;
struct wil6210_priv {int** ring2cid_tid; int max_assoc_sta; int /*<<< orphan*/  tx_sring_idx; int /*<<< orphan*/  mutex; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;

/* Variables and functions */
 scalar_t__ agg_wsize ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_addba_tx_request (struct wil6210_priv*,int,scalar_t__) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int wil_ring_alloc_desc_ring (struct wil6210_priv*,struct wil_ring*) ; 
 int /*<<< orphan*/  wil_ring_free_edma (struct wil6210_priv*,struct wil_ring*) ; 
 int /*<<< orphan*/  wil_tx_data_init (struct wil_ring_tx_data*) ; 
 int wil_wmi_tx_desc_ring_add (struct wil6210_vif*,int,int,int) ; 

__attribute__((used)) static int wil_ring_init_tx_edma(struct wil6210_vif *vif, int ring_id,
				 int size, int cid, int tid)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	int rc;
	struct wil_ring *ring = &wil->ring_tx[ring_id];
	struct wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];

	lockdep_assert_held(&wil->mutex);

	wil_dbg_misc(wil,
		     "init TX ring: ring_id=%u, cid=%u, tid=%u, sring_id=%u\n",
		     ring_id, cid, tid, wil->tx_sring_idx);

	wil_tx_data_init(txdata);
	ring->size = size;
	rc = wil_ring_alloc_desc_ring(wil, ring);
	if (rc)
		goto out;

	wil->ring2cid_tid[ring_id][0] = cid;
	wil->ring2cid_tid[ring_id][1] = tid;
	if (!vif->privacy)
		txdata->dot1x_open = true;

	rc = wil_wmi_tx_desc_ring_add(vif, ring_id, cid, tid);
	if (rc) {
		wil_err(wil, "WMI_TX_DESC_RING_ADD_CMD failed\n");
		goto out_free;
	}

	if (txdata->dot1x_open && agg_wsize >= 0)
		wil_addba_tx_request(wil, ring_id, agg_wsize);

	return 0;
 out_free:
	spin_lock_bh(&txdata->lock);
	txdata->dot1x_open = false;
	txdata->enabled = 0;
	spin_unlock_bh(&txdata->lock);
	wil_ring_free_edma(wil, ring);
	wil->ring2cid_tid[ring_id][0] = wil->max_assoc_sta;
	wil->ring2cid_tid[ring_id][1] = 0;

 out:
	return rc;
}