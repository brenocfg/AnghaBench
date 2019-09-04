#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct sk_buff {int len; void* protocol; struct arc_rfc1201* data; struct net_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct arphdr {int ar_hln; int ar_pln; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* copy_from_card ) (struct net_device*,int,int,struct arc_rfc1201*,int) ;} ;
struct TYPE_10__ {int aborted_seq; struct Incoming* incoming; } ;
struct arcnet_local {TYPE_2__ hw; TYPE_5__ rfc1201; } ;
struct TYPE_9__ {int source; } ;
struct arc_rfc1201 {int split_flag; int sequence; scalar_t__ proto; scalar_t__ payload; } ;
struct TYPE_8__ {struct arc_rfc1201 rfc1201; struct arc_rfc1201* raw; } ;
struct archdr {TYPE_4__ hard; TYPE_3__ soft; } ;
struct Incoming {int sequence; int lastpacket; int numpackets; struct sk_buff* skb; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 scalar_t__ ARC_P_ARP ; 
 scalar_t__ BUGLVL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_EXTRA ; 
 int /*<<< orphan*/  D_NORMAL ; 
 int /*<<< orphan*/  D_RX ; 
 int /*<<< orphan*/  D_SKB ; 
 int /*<<< orphan*/  D_SKB_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MinTU ; 
 int RFC1201_HDR_SIZE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  arcnet_dump_skb (struct net_device*,struct sk_buff*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct archdr*,struct archdr*,int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 
 void* type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void rx(struct net_device *dev, int bufnum,
	       struct archdr *pkthdr, int length)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct sk_buff *skb;
	struct archdr *pkt = pkthdr;
	struct arc_rfc1201 *soft = &pkthdr->soft.rfc1201;
	int saddr = pkt->hard.source, ofs;
	struct Incoming *in = &lp->rfc1201.incoming[saddr];

	arc_printk(D_DURING, dev, "it's an RFC1201 packet (length=%d)\n",
		   length);

	if (length >= MinTU)
		ofs = 512 - length;
	else
		ofs = 256 - length;

	if (soft->split_flag == 0xFF) {		/* Exception Packet */
		if (length >= 4 + RFC1201_HDR_SIZE) {
			arc_printk(D_DURING, dev, "compensating for exception packet\n");
		} else {
			arc_printk(D_EXTRA, dev, "short RFC1201 exception packet from %02Xh",
				   saddr);
			return;
		}

		/* skip over 4-byte junkola */
		length -= 4;
		ofs += 4;
		lp->hw.copy_from_card(dev, bufnum, 512 - length,
				      soft, sizeof(pkt->soft));
	}
	if (!soft->split_flag) {	/* not split */
		arc_printk(D_RX, dev, "incoming is not split (splitflag=%d)\n",
			   soft->split_flag);

		if (in->skb) {	/* already assembling one! */
			arc_printk(D_EXTRA, dev, "aborting assembly (seq=%d) for unsplit packet (splitflag=%d, seq=%d)\n",
				   in->sequence, soft->split_flag,
				   soft->sequence);
			lp->rfc1201.aborted_seq = soft->sequence;
			dev_kfree_skb_irq(in->skb);
			dev->stats.rx_errors++;
			dev->stats.rx_missed_errors++;
			in->skb = NULL;
		}
		in->sequence = soft->sequence;

		skb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
		if (!skb) {
			dev->stats.rx_dropped++;
			return;
		}
		skb_put(skb, length + ARC_HDR_SIZE);
		skb->dev = dev;

		pkt = (struct archdr *)skb->data;
		soft = &pkt->soft.rfc1201;

		/* up to sizeof(pkt->soft) has already
		 * been copied from the card
		 */
		memcpy(pkt, pkthdr, sizeof(struct archdr));
		if (length > sizeof(pkt->soft))
			lp->hw.copy_from_card(dev, bufnum,
					      ofs + sizeof(pkt->soft),
					      pkt->soft.raw + sizeof(pkt->soft),
					      length - sizeof(pkt->soft));

		/* ARP packets have problems when sent from some DOS systems:
		 * the source address is always 0!
		 * So we take the hardware source addr (which is impossible
		 * to fumble) and insert it ourselves.
		 */
		if (soft->proto == ARC_P_ARP) {
			struct arphdr *arp = (struct arphdr *)soft->payload;

			/* make sure addresses are the right length */
			if (arp->ar_hln == 1 && arp->ar_pln == 4) {
				uint8_t *cptr = (uint8_t *)arp + sizeof(struct arphdr);

				if (!*cptr) {	/* is saddr = 00? */
					arc_printk(D_EXTRA, dev,
						   "ARP source address was 00h, set to %02Xh\n",
						   saddr);
					dev->stats.rx_crc_errors++;
					*cptr = saddr;
				} else {
					arc_printk(D_DURING, dev, "ARP source address (%Xh) is fine.\n",
						   *cptr);
				}
			} else {
				arc_printk(D_NORMAL, dev, "funny-shaped ARP packet. (%Xh, %Xh)\n",
					   arp->ar_hln, arp->ar_pln);
				dev->stats.rx_errors++;
				dev->stats.rx_crc_errors++;
			}
		}
		if (BUGLVL(D_SKB))
			arcnet_dump_skb(dev, skb, "rx");

		skb->protocol = type_trans(skb, dev);
		netif_rx(skb);
	} else {		/* split packet */
		/* NOTE: MSDOS ARP packet correction should only need to
		 * apply to unsplit packets, since ARP packets are so short.
		 *
		 * My interpretation of the RFC1201 document is that if a
		 * packet is received out of order, the entire assembly
		 * process should be aborted.
		 *
		 * The RFC also mentions "it is possible for successfully
		 * received packets to be retransmitted." As of 0.40 all
		 * previously received packets are allowed, not just the
		 * most recent one.
		 *
		 * We allow multiple assembly processes, one for each
		 * ARCnet card possible on the network.
		 * Seems rather like a waste of memory, but there's no
		 * other way to be reliable.
		 */

		arc_printk(D_RX, dev, "packet is split (splitflag=%d, seq=%d)\n",
			   soft->split_flag, in->sequence);

		if (in->skb && in->sequence != soft->sequence) {
			arc_printk(D_EXTRA, dev, "wrong seq number (saddr=%d, expected=%d, seq=%d, splitflag=%d)\n",
				   saddr, in->sequence, soft->sequence,
				   soft->split_flag);
			dev_kfree_skb_irq(in->skb);
			in->skb = NULL;
			dev->stats.rx_errors++;
			dev->stats.rx_missed_errors++;
			in->lastpacket = in->numpackets = 0;
		}
		if (soft->split_flag & 1) {	/* first packet in split */
			arc_printk(D_RX, dev, "brand new splitpacket (splitflag=%d)\n",
				   soft->split_flag);
			if (in->skb) {	/* already assembling one! */
				arc_printk(D_EXTRA, dev, "aborting previous (seq=%d) assembly (splitflag=%d, seq=%d)\n",
					   in->sequence, soft->split_flag,
					   soft->sequence);
				dev->stats.rx_errors++;
				dev->stats.rx_missed_errors++;
				dev_kfree_skb_irq(in->skb);
			}
			in->sequence = soft->sequence;
			in->numpackets = ((unsigned)soft->split_flag >> 1) + 2;
			in->lastpacket = 1;

			if (in->numpackets > 16) {
				arc_printk(D_EXTRA, dev, "incoming packet more than 16 segments; dropping. (splitflag=%d)\n",
					   soft->split_flag);
				lp->rfc1201.aborted_seq = soft->sequence;
				dev->stats.rx_errors++;
				dev->stats.rx_length_errors++;
				return;
			}
			in->skb = skb = alloc_skb(508 * in->numpackets + ARC_HDR_SIZE,
						  GFP_ATOMIC);
			if (!skb) {
				arc_printk(D_NORMAL, dev, "(split) memory squeeze, dropping packet.\n");
				lp->rfc1201.aborted_seq = soft->sequence;
				dev->stats.rx_dropped++;
				return;
			}
			skb->dev = dev;
			pkt = (struct archdr *)skb->data;
			soft = &pkt->soft.rfc1201;

			memcpy(pkt, pkthdr, ARC_HDR_SIZE + RFC1201_HDR_SIZE);
			skb_put(skb, ARC_HDR_SIZE + RFC1201_HDR_SIZE);

			soft->split_flag = 0;	/* end result won't be split */
		} else {	/* not first packet */
			int packetnum = ((unsigned)soft->split_flag >> 1) + 1;

			/* if we're not assembling, there's no point trying to
			 * continue.
			 */
			if (!in->skb) {
				if (lp->rfc1201.aborted_seq != soft->sequence) {
					arc_printk(D_EXTRA, dev, "can't continue split without starting first! (splitflag=%d, seq=%d, aborted=%d)\n",
						   soft->split_flag,
						   soft->sequence,
						   lp->rfc1201.aborted_seq);
					dev->stats.rx_errors++;
					dev->stats.rx_missed_errors++;
				}
				return;
			}
			in->lastpacket++;
			/* if not the right flag */
			if (packetnum != in->lastpacket) {
				/* harmless duplicate? ignore. */
				if (packetnum <= in->lastpacket - 1) {
					arc_printk(D_EXTRA, dev, "duplicate splitpacket ignored! (splitflag=%d)\n",
						   soft->split_flag);
					dev->stats.rx_errors++;
					dev->stats.rx_frame_errors++;
					return;
				}
				/* "bad" duplicate, kill reassembly */
				arc_printk(D_EXTRA, dev, "out-of-order splitpacket, reassembly (seq=%d) aborted (splitflag=%d, seq=%d)\n",
					   in->sequence, soft->split_flag,
					   soft->sequence);
				lp->rfc1201.aborted_seq = soft->sequence;
				dev_kfree_skb_irq(in->skb);
				in->skb = NULL;
				dev->stats.rx_errors++;
				dev->stats.rx_missed_errors++;
				in->lastpacket = in->numpackets = 0;
				return;
			}
			pkt = (struct archdr *)in->skb->data;
			soft = &pkt->soft.rfc1201;
		}

		skb = in->skb;

		lp->hw.copy_from_card(dev, bufnum, ofs + RFC1201_HDR_SIZE,
				      skb->data + skb->len,
				      length - RFC1201_HDR_SIZE);
		skb_put(skb, length - RFC1201_HDR_SIZE);

		/* are we done? */
		if (in->lastpacket == in->numpackets) {
			in->skb = NULL;
			in->lastpacket = in->numpackets = 0;

			arc_printk(D_SKB_SIZE, dev, "skb: received %d bytes from %02X (unsplit)\n",
				   skb->len, pkt->hard.source);
			arc_printk(D_SKB_SIZE, dev, "skb: received %d bytes from %02X (split)\n",
				   skb->len, pkt->hard.source);
			if (BUGLVL(D_SKB))
				arcnet_dump_skb(dev, skb, "rx");

			skb->protocol = type_trans(skb, dev);
			netif_rx(skb);
		}
	}
}