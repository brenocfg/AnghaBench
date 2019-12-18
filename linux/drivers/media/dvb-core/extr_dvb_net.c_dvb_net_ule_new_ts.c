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
struct dvb_net_ule_handle {int* ts; int* from_where; int ts_remain; int error; TYPE_3__* priv; TYPE_2__* dev; } ;
struct TYPE_6__ {int tscc; int need_pusi; int ule_sndu_remain; scalar_t__ ule_skb; int /*<<< orphan*/  ts_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int TS_PUSI ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  reset_ule (TYPE_3__*) ; 

__attribute__((used)) static int dvb_net_ule_new_ts(struct dvb_net_ule_handle *h)
{
	/* Check continuity counter. */
	if ((h->ts[3] & 0x0F) == h->priv->tscc)
		h->priv->tscc = (h->priv->tscc + 1) & 0x0F;
	else {
		/* TS discontinuity handling: */
		pr_warn("%lu: TS discontinuity: got %#x, expected %#x.\n",
			h->priv->ts_count, h->ts[3] & 0x0F,
			h->priv->tscc);
		/* Drop partly decoded SNDU, reset state, resync on PUSI. */
		if (h->priv->ule_skb) {
			dev_kfree_skb(h->priv->ule_skb);
			/* Prepare for next SNDU. */
			// reset_ule(h->priv);  moved to below.
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_frame_errors++;
		}
		reset_ule(h->priv);
		/* skip to next PUSI. */
		h->priv->need_pusi = 1;
		return 1;
	}
	/*
	 * If we still have an incomplete payload, but PUSI is
	 * set; some TS cells are missing.
	 * This is only possible here, if we missed exactly 16 TS
	 * cells (continuity counter wrap).
	 */
	if (h->ts[1] & TS_PUSI) {
		if (!h->priv->need_pusi) {
			if (!(*h->from_where < (h->ts_remain-1)) ||
			    *h->from_where != h->priv->ule_sndu_remain) {
				/*
				 * Pointer field is invalid.
				 * Drop this TS cell and any started ULE SNDU.
				 */
				pr_warn("%lu: Invalid pointer field: %u.\n",
					h->priv->ts_count,
					*h->from_where);

				/*
				 * Drop partly decoded SNDU, reset state,
				 * resync on PUSI.
				 */
				if (h->priv->ule_skb) {
					h->error = true;
					dev_kfree_skb(h->priv->ule_skb);
				}

				if (h->error || h->priv->ule_sndu_remain) {
					h->dev->stats.rx_errors++;
					h->dev->stats.rx_frame_errors++;
					h->error = false;
				}

				reset_ule(h->priv);
				h->priv->need_pusi = 1;
				return 1;
			}
			/*
			 * Skip pointer field (we're processing a
			 * packed payload).
			 */
			h->from_where += 1;
			h->ts_remain -= 1;
		} else
			h->priv->need_pusi = 0;

		if (h->priv->ule_sndu_remain > 183) {
			/*
			 * Current SNDU lacks more data than there
			 * could be available in the current TS cell.
			 */
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_length_errors++;
			pr_warn("%lu: Expected %d more SNDU bytes, but got PUSI (pf %d, h->ts_remain %d).  Flushing incomplete payload.\n",
				h->priv->ts_count,
				h->priv->ule_sndu_remain,
				h->ts[4], h->ts_remain);
			dev_kfree_skb(h->priv->ule_skb);
			/* Prepare for next SNDU. */
			reset_ule(h->priv);
			/*
			 * Resync: go to where pointer field points to:
			 * start of next ULE SNDU.
			 */
			h->from_where += h->ts[4];
			h->ts_remain -= h->ts[4];
		}
	}
	return 0;
}