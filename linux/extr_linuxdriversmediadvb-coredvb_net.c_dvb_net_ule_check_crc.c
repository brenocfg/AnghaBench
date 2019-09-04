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
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct kvec {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/ * h_source; int /*<<< orphan*/  h_dest; } ;
struct dvb_net_ule_handle {int ts_remain; TYPE_7__* priv; TYPE_6__* dev; struct ethhdr* ethh; scalar_t__ from_where; } ;
struct TYPE_14__ {scalar_t__ ule_sndu_type; TYPE_2__* ule_skb; scalar_t__ ule_bridged; int /*<<< orphan*/  ule_dbit; int /*<<< orphan*/  ule_sndu_len; int /*<<< orphan*/  ts_count; } ;
struct TYPE_11__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_13__ {TYPE_1__ stats; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_12__ {int tail; scalar_t__ len; int /*<<< orphan*/  protocol; scalar_t__ data; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 scalar_t__ ETH_P_802_3_MIN ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_net_eth_type_trans (TYPE_2__*,TYPE_6__*) ; 
 scalar_t__ dvb_net_ule_should_drop (struct dvb_net_ule_handle*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int handle_ule_extensions (TYPE_7__*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_6__*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,unsigned short) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_pull (TYPE_2__*,int) ; 
 int /*<<< orphan*/  skb_push (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvb_net_ule_check_crc(struct dvb_net_ule_handle *h,
				  struct kvec iov[3],
				  u32 ule_crc, u32 expected_crc)
{
	u8 dest_addr[ETH_ALEN];

	if (ule_crc != expected_crc) {
		pr_warn("%lu: CRC32 check FAILED: %08x / %08x, SNDU len %d type %#x, ts_remain %d, next 2: %x.\n",
			h->priv->ts_count, ule_crc, expected_crc,
			h->priv->ule_sndu_len, h->priv->ule_sndu_type,
			h->ts_remain,
			h->ts_remain > 2 ?
				*(unsigned short *)h->from_where : 0);

	#ifdef DVB_ULE_DEBUG
		hexdump(iov[0].iov_base, iov[0].iov_len);
		hexdump(iov[1].iov_base, iov[1].iov_len);
		hexdump(iov[2].iov_base, iov[2].iov_len);

		if (ule_where == ule_hist) {
			hexdump(&ule_hist[98*TS_SZ], TS_SZ);
			hexdump(&ule_hist[99*TS_SZ], TS_SZ);
		} else if (ule_where == &ule_hist[TS_SZ]) {
			hexdump(&ule_hist[99*TS_SZ], TS_SZ);
			hexdump(ule_hist, TS_SZ);
		} else {
			hexdump(ule_where - TS_SZ - TS_SZ, TS_SZ);
			hexdump(ule_where - TS_SZ, TS_SZ);
		}
		ule_dump = 1;
	#endif

		h->dev->stats.rx_errors++;
		h->dev->stats.rx_crc_errors++;
		dev_kfree_skb(h->priv->ule_skb);

		return;
	}

	/* CRC32 verified OK. */

	/* CRC32 was OK, so remove it from skb. */
	h->priv->ule_skb->tail -= 4;
	h->priv->ule_skb->len -= 4;

	if (!h->priv->ule_dbit) {
		if (dvb_net_ule_should_drop(h)) {
			netdev_dbg(h->dev,
				   "Dropping SNDU: MAC destination address does not match: dest addr: %pM, h->dev addr: %pM\n",
				   h->priv->ule_skb->data, h->dev->dev_addr);
			dev_kfree_skb(h->priv->ule_skb);
			return;
		}

		skb_copy_from_linear_data(h->priv->ule_skb, dest_addr,
					  ETH_ALEN);
		skb_pull(h->priv->ule_skb, ETH_ALEN);
	} else {
		/* dest_addr buffer is only valid if h->priv->ule_dbit == 0 */
		eth_zero_addr(dest_addr);
	}

	/* Handle ULE Extension Headers. */
	if (h->priv->ule_sndu_type < ETH_P_802_3_MIN) {
		/* There is an extension header.  Handle it accordingly. */
		int l = handle_ule_extensions(h->priv);

		if (l < 0) {
			/*
			 * Mandatory extension header unknown or TEST SNDU.
			 * Drop it.
			 */

			// pr_warn("Dropping SNDU, extension headers.\n" );
			dev_kfree_skb(h->priv->ule_skb);
			return;
		}
		skb_pull(h->priv->ule_skb, l);
	}

	/*
	 * Construct/assure correct ethernet header.
	 * Note: in bridged mode (h->priv->ule_bridged != 0)
	 * we already have the (original) ethernet
	 * header at the start of the payload (after
	 * optional dest. address and any extension
	 * headers).
	 */
	if (!h->priv->ule_bridged) {
		skb_push(h->priv->ule_skb, ETH_HLEN);
		h->ethh = (struct ethhdr *)h->priv->ule_skb->data;
		memcpy(h->ethh->h_dest, dest_addr, ETH_ALEN);
		eth_zero_addr(h->ethh->h_source);
		h->ethh->h_proto = htons(h->priv->ule_sndu_type);
	}
	/* else:  skb is in correct state; nothing to do. */
	h->priv->ule_bridged = 0;

	/* Stuff into kernel's protocol stack. */
	h->priv->ule_skb->protocol = dvb_net_eth_type_trans(h->priv->ule_skb,
							   h->dev);
	/*
	 * If D-bit is set (i.e. destination MAC address not present),
	 * receive the packet anyhow.
	 */
#if 0
	if (h->priv->ule_dbit && skb->pkt_type == PACKET_OTHERHOST)
		h->priv->ule_skb->pkt_type = PACKET_HOST;
#endif
	h->dev->stats.rx_packets++;
	h->dev->stats.rx_bytes += h->priv->ule_skb->len;
	netif_rx(h->priv->ule_skb);
}