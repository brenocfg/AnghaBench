#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_net_ule_handle {int* ts; int ts_remain; int* from_where; TYPE_3__* priv; TYPE_2__* dev; } ;
struct TYPE_6__ {int need_pusi; int /*<<< orphan*/  ts_count; scalar_t__ ule_skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int TS_SC ; 
 int TS_SYNC ; 
 int TS_SZ ; 
 int TS_TEI ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  reset_ule (TYPE_3__*) ; 
 scalar_t__ ule_dump ; 
 int /*<<< orphan*/ * ule_hist ; 
 int /*<<< orphan*/ * ule_where ; 

__attribute__((used)) static int dvb_net_ule_new_ts_cell(struct dvb_net_ule_handle *h)
{
	/* We are about to process a new TS cell. */

#ifdef DVB_ULE_DEBUG
	if (ule_where >= &ule_hist[100*TS_SZ])
		ule_where = ule_hist;
	memcpy(ule_where, h->ts, TS_SZ);
	if (ule_dump) {
		hexdump(ule_where, TS_SZ);
		ule_dump = 0;
	}
	ule_where += TS_SZ;
#endif

	/*
	 * Check TS h->error conditions: sync_byte, transport_error_indicator,
	 * scrambling_control .
	 */
	if ((h->ts[0] != TS_SYNC) || (h->ts[1] & TS_TEI) ||
	    ((h->ts[3] & TS_SC) != 0)) {
		pr_warn("%lu: Invalid TS cell: SYNC %#x, TEI %u, SC %#x.\n",
			h->priv->ts_count, h->ts[0],
			(h->ts[1] & TS_TEI) >> 7,
			(h->ts[3] & TS_SC) >> 6);

		/* Drop partly decoded SNDU, reset state, resync on PUSI. */
		if (h->priv->ule_skb) {
			dev_kfree_skb(h->priv->ule_skb);
			/* Prepare for next SNDU. */
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_frame_errors++;
		}
		reset_ule(h->priv);
		h->priv->need_pusi = 1;

		/* Continue with next TS cell. */
		h->ts += TS_SZ;
		h->priv->ts_count++;
		return 1;
	}

	h->ts_remain = 184;
	h->from_where = h->ts + 4;

	return 0;
}