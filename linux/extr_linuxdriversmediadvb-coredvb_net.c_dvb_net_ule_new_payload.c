#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dvb_net_ule_handle {int ts_remain; int* from_where; int new_ts; TYPE_3__* priv; TYPE_2__* dev; int /*<<< orphan*/  ts; } ;
struct TYPE_9__ {TYPE_2__* dev; } ;
struct TYPE_8__ {int ule_sndu_len; int need_pusi; int ule_dbit; int ule_sndu_remain; int ule_sndu_type; int ule_sndu_type_1; TYPE_4__* ule_skb; int /*<<< orphan*/  ts_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_7__ {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ TS_SZ ; 
 TYPE_4__* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int dvb_net_ule_new_payload(struct dvb_net_ule_handle *h)
{
	if (h->ts_remain < 2) {
		pr_warn("Invalid payload packing: only %d bytes left in TS.  Resyncing.\n",
			h->ts_remain);
		h->priv->ule_sndu_len = 0;
		h->priv->need_pusi = 1;
		h->ts += TS_SZ;
		return 1;
	}

	if (!h->priv->ule_sndu_len) {
		/* Got at least two bytes, thus extrace the SNDU length. */
		h->priv->ule_sndu_len = h->from_where[0] << 8 |
					h->from_where[1];
		if (h->priv->ule_sndu_len & 0x8000) {
			/* D-Bit is set: no dest mac present. */
			h->priv->ule_sndu_len &= 0x7FFF;
			h->priv->ule_dbit = 1;
		} else
			h->priv->ule_dbit = 0;

		if (h->priv->ule_sndu_len < 5) {
			pr_warn("%lu: Invalid ULE SNDU length %u. Resyncing.\n",
				h->priv->ts_count,
				h->priv->ule_sndu_len);
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_length_errors++;
			h->priv->ule_sndu_len = 0;
			h->priv->need_pusi = 1;
			h->new_ts = 1;
			h->ts += TS_SZ;
			h->priv->ts_count++;
			return 1;
		}
		h->ts_remain -= 2;	/* consume the 2 bytes SNDU length. */
		h->from_where += 2;
	}

	h->priv->ule_sndu_remain = h->priv->ule_sndu_len + 2;
	/*
	 * State of current TS:
	 *   h->ts_remain (remaining bytes in the current TS cell)
	 *   0	ule_type is not available now, we need the next TS cell
	 *   1	the first byte of the ule_type is present
	 * >=2	full ULE header present, maybe some payload data as well.
	 */
	switch (h->ts_remain) {
	case 1:
		h->priv->ule_sndu_remain--;
		h->priv->ule_sndu_type = h->from_where[0] << 8;

		/* first byte of ule_type is set. */
		h->priv->ule_sndu_type_1 = 1;
		h->ts_remain -= 1;
		h->from_where += 1;
		/* fallthrough */
	case 0:
		h->new_ts = 1;
		h->ts += TS_SZ;
		h->priv->ts_count++;
		return 1;

	default: /* complete ULE header is present in current TS. */
		/* Extract ULE type field. */
		if (h->priv->ule_sndu_type_1) {
			h->priv->ule_sndu_type_1 = 0;
			h->priv->ule_sndu_type |= h->from_where[0];
			h->from_where += 1; /* points to payload start. */
			h->ts_remain -= 1;
		} else {
			/* Complete type is present in new TS. */
			h->priv->ule_sndu_type = h->from_where[0] << 8 |
						 h->from_where[1];
			h->from_where += 2; /* points to payload start. */
			h->ts_remain -= 2;
		}
		break;
	}

	/*
	 * Allocate the skb (decoder target buffer) with the correct size,
	 * as follows:
	 *
	 * prepare for the largest case: bridged SNDU with MAC address
	 * (dbit = 0).
	 */
	h->priv->ule_skb = dev_alloc_skb(h->priv->ule_sndu_len +
					 ETH_HLEN + ETH_ALEN);
	if (!h->priv->ule_skb) {
		pr_notice("%s: Memory squeeze, dropping packet.\n",
			  h->dev->name);
		h->dev->stats.rx_dropped++;
		return -1;
	}

	/* This includes the CRC32 _and_ dest mac, if !dbit. */
	h->priv->ule_sndu_remain = h->priv->ule_sndu_len;
	h->priv->ule_skb->dev = h->dev;
	/*
	 * Leave space for Ethernet or bridged SNDU header
	 * (eth hdr plus one MAC addr).
	 */
	skb_reserve(h->priv->ule_skb, ETH_HLEN + ETH_ALEN);

	return 0;
}