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
typedef  int u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {int /*<<< orphan*/  name; struct net_device_stats stats; } ;

/* Variables and functions */
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dvb_net_eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void dvb_net_sec(struct net_device *dev,
			const u8 *pkt, int pkt_len)
{
	u8 *eth;
	struct sk_buff *skb;
	struct net_device_stats *stats = &dev->stats;
	int snap = 0;

	/* note: pkt_len includes a 32bit checksum */
	if (pkt_len < 16) {
		pr_warn("%s: IP/MPE packet length = %d too small.\n",
			dev->name, pkt_len);
		stats->rx_errors++;
		stats->rx_length_errors++;
		return;
	}
/* it seems some ISPs manage to screw up here, so we have to
 * relax the error checks... */
#if 0
	if ((pkt[5] & 0xfd) != 0xc1) {
		/* drop scrambled or broken packets */
#else
	if ((pkt[5] & 0x3c) != 0x00) {
		/* drop scrambled */
#endif
		stats->rx_errors++;
		stats->rx_crc_errors++;
		return;
	}
	if (pkt[5] & 0x02) {
		/* handle LLC/SNAP, see rfc-1042 */
		if (pkt_len < 24 || memcmp(&pkt[12], "\xaa\xaa\x03\0\0\0", 6)) {
			stats->rx_dropped++;
			return;
		}
		snap = 8;
	}
	if (pkt[7]) {
		/* FIXME: assemble datagram from multiple sections */
		stats->rx_errors++;
		stats->rx_frame_errors++;
		return;
	}

	/* we have 14 byte ethernet header (ip header follows);
	 * 12 byte MPE header; 4 byte checksum; + 2 byte alignment, 8 byte LLC/SNAP
	 */
	if (!(skb = dev_alloc_skb(pkt_len - 4 - 12 + 14 + 2 - snap))) {
		//pr_notice("%s: Memory squeeze, dropping packet.\n", dev->name);
		stats->rx_dropped++;
		return;
	}
	skb_reserve(skb, 2);    /* longword align L3 header */
	skb->dev = dev;

	/* copy L3 payload */
	eth = skb_put(skb, pkt_len - 12 - 4 + 14 - snap);
	memcpy(eth + 14, pkt + 12 + snap, pkt_len - 12 - 4 - snap);

	/* create ethernet header: */
	eth[0]=pkt[0x0b];
	eth[1]=pkt[0x0a];
	eth[2]=pkt[0x09];
	eth[3]=pkt[0x08];
	eth[4]=pkt[0x04];
	eth[5]=pkt[0x03];

	eth[6]=eth[7]=eth[8]=eth[9]=eth[10]=eth[11]=0;

	if (snap) {
		eth[12] = pkt[18];
		eth[13] = pkt[19];
	} else {
		/* protocol numbers are from rfc-1700 or
		 * http://www.iana.org/assignments/ethernet-numbers
		 */
		if (pkt[12] >> 4 == 6) { /* version field from IP header */
			eth[12] = 0x86;	/* IPv6 */
			eth[13] = 0xdd;
		} else {
			eth[12] = 0x08;	/* IPv4 */
			eth[13] = 0x00;
		}
	}

	skb->protocol = dvb_net_eth_type_trans(skb, dev);

	stats->rx_packets++;
	stats->rx_bytes+=skb->len;
	netif_rx(skb);
}