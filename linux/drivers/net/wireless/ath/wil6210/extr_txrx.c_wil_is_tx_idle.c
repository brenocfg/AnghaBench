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
struct wil_ring_tx_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled; } ;
struct wil_ring {int /*<<< orphan*/  va; } ;
struct wil6210_priv {int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  status; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;

/* Variables and functions */
 int WIL6210_MAX_TX_RINGS ; 
 int /*<<< orphan*/  WIL_DATA_COMPLETION_TO_MS ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wil_dbg_pm (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_dbg_ratelimited (struct wil6210_priv*,char*) ; 
 int wil_get_min_tx_ring_id (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_ring_is_empty (struct wil_ring*) ; 
 int /*<<< orphan*/  wil_status_napi_en ; 

bool wil_is_tx_idle(struct wil6210_priv *wil)
{
	int i;
	unsigned long data_comp_to;
	int min_ring_id = wil_get_min_tx_ring_id(wil);

	for (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) {
		struct wil_ring *vring = &wil->ring_tx[i];
		int vring_index = vring - wil->ring_tx;
		struct wil_ring_tx_data *txdata =
			&wil->ring_tx_data[vring_index];

		spin_lock(&txdata->lock);

		if (!vring->va || !txdata->enabled) {
			spin_unlock(&txdata->lock);
			continue;
		}

		data_comp_to = jiffies + msecs_to_jiffies(
					WIL_DATA_COMPLETION_TO_MS);
		if (test_bit(wil_status_napi_en, wil->status)) {
			while (!wil_ring_is_empty(vring)) {
				if (time_after(jiffies, data_comp_to)) {
					wil_dbg_pm(wil,
						   "TO waiting for idle tx\n");
					spin_unlock(&txdata->lock);
					return false;
				}
				wil_dbg_ratelimited(wil,
						    "tx vring is not empty -> NAPI\n");
				spin_unlock(&txdata->lock);
				napi_synchronize(&wil->napi_tx);
				msleep(20);
				spin_lock(&txdata->lock);
				if (!vring->va || !txdata->enabled)
					break;
			}
		}

		spin_unlock(&txdata->lock);
	}

	return true;
}