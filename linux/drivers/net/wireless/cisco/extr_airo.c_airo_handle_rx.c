#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * dev; int /*<<< orphan*/  pkt_type; } ;
struct rx_hdr {size_t* rssi; scalar_t__ len; scalar_t__ status; } ;
struct iw_quality {size_t qual; int level; int updated; int /*<<< orphan*/  noise; } ;
struct TYPE_15__ {int /*<<< orphan*/  noise; } ;
struct TYPE_16__ {TYPE_5__ qual; } ;
struct TYPE_13__ {scalar_t__ spy_number; } ;
struct TYPE_12__ {scalar_t__ enabled; } ;
struct airo_info {TYPE_8__* dev; int /*<<< orphan*/ * wifidev; int /*<<< orphan*/  flags; TYPE_6__ wstats; TYPE_4__* rssi; TYPE_3__ spy_data; TYPE_2__ micstats; } ;
typedef  int /*<<< orphan*/  micbuf ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  fc ;
typedef  int /*<<< orphan*/  etherHead ;
typedef  scalar_t__ __le16 ;
struct TYPE_11__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct TYPE_17__ {int /*<<< orphan*/  typelen; } ;
struct TYPE_14__ {int rssidBm; } ;
typedef  TYPE_7__ MICBuffer ;

/* Variables and functions */
 int AIRO_DEF_MTU ; 
 int /*<<< orphan*/  BAP0 ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EV_RX ; 
 int /*<<< orphan*/  FLAG_802_11 ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int IW_QUAL_DBM ; 
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_QUAL_UPDATED ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  RXFID ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bap_read (struct airo_info*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bap_setup (struct airo_info*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ decapsulate (struct airo_info*,TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_8__*) ; 
 int header_len (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mpi_receive_802_11 (struct airo_info*) ; 
 int /*<<< orphan*/  mpi_receive_802_3 (struct airo_info*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireless_spy_update (TYPE_8__*,char*,struct iw_quality*) ; 

__attribute__((used)) static void airo_handle_rx(struct airo_info *ai)
{
	struct sk_buff *skb = NULL;
	__le16 fc, v, *buffer, tmpbuf[4];
	u16 len, hdrlen = 0, gap, fid;
	struct rx_hdr hdr;
	int success = 0;

	if (test_bit(FLAG_MPI, &ai->flags)) {
		if (test_bit(FLAG_802_11, &ai->flags))
			mpi_receive_802_11(ai);
		else
			mpi_receive_802_3(ai);
		OUT4500(ai, EVACK, EV_RX);
		return;
	}

	fid = IN4500(ai, RXFID);

	/* Get the packet length */
	if (test_bit(FLAG_802_11, &ai->flags)) {
		bap_setup (ai, fid, 4, BAP0);
		bap_read (ai, (__le16*)&hdr, sizeof(hdr), BAP0);
		/* Bad CRC. Ignore packet */
		if (le16_to_cpu(hdr.status) & 2)
			hdr.len = 0;
		if (ai->wifidev == NULL)
			hdr.len = 0;
	} else {
		bap_setup(ai, fid, 0x36, BAP0);
		bap_read(ai, &hdr.len, 2, BAP0);
	}
	len = le16_to_cpu(hdr.len);

	if (len > AIRO_DEF_MTU) {
		airo_print_err(ai->dev->name, "Bad size %d", len);
		goto done;
	}
	if (len == 0)
		goto done;

	if (test_bit(FLAG_802_11, &ai->flags)) {
		bap_read(ai, &fc, sizeof (fc), BAP0);
		hdrlen = header_len(fc);
	} else
		hdrlen = ETH_ALEN * 2;

	skb = dev_alloc_skb(len + hdrlen + 2 + 2);
	if (!skb) {
		ai->dev->stats.rx_dropped++;
		goto done;
	}

	skb_reserve(skb, 2); /* This way the IP header is aligned */
	buffer = skb_put(skb, len + hdrlen);
	if (test_bit(FLAG_802_11, &ai->flags)) {
		buffer[0] = fc;
		bap_read(ai, buffer + 1, hdrlen - 2, BAP0);
		if (hdrlen == 24)
			bap_read(ai, tmpbuf, 6, BAP0);

		bap_read(ai, &v, sizeof(v), BAP0);
		gap = le16_to_cpu(v);
		if (gap) {
			if (gap <= 8) {
				bap_read(ai, tmpbuf, gap, BAP0);
			} else {
				airo_print_err(ai->dev->name, "gaplen too "
					"big. Problems will follow...");
			}
		}
		bap_read(ai, buffer + hdrlen/2, len, BAP0);
	} else {
		MICBuffer micbuf;

		bap_read(ai, buffer, ETH_ALEN * 2, BAP0);
		if (ai->micstats.enabled) {
			bap_read(ai, (__le16 *) &micbuf, sizeof (micbuf), BAP0);
			if (ntohs(micbuf.typelen) > 0x05DC)
				bap_setup(ai, fid, 0x44, BAP0);
			else {
				if (len <= sizeof (micbuf)) {
					dev_kfree_skb_irq(skb);
					goto done;
				}

				len -= sizeof(micbuf);
				skb_trim(skb, len + hdrlen);
			}
		}

		bap_read(ai, buffer + ETH_ALEN, len, BAP0);
		if (decapsulate(ai, &micbuf, (etherHead*) buffer, len))
			dev_kfree_skb_irq (skb);
		else
			success = 1;
	}

#ifdef WIRELESS_SPY
	if (success && (ai->spy_data.spy_number > 0)) {
		char *sa;
		struct iw_quality wstats;

		/* Prepare spy data : addr + qual */
		if (!test_bit(FLAG_802_11, &ai->flags)) {
			sa = (char *) buffer + 6;
			bap_setup(ai, fid, 8, BAP0);
			bap_read(ai, (__le16 *) hdr.rssi, 2, BAP0);
		} else
			sa = (char *) buffer + 10;
		wstats.qual = hdr.rssi[0];
		if (ai->rssi)
			wstats.level = 0x100 - ai->rssi[hdr.rssi[1]].rssidBm;
		else
			wstats.level = (hdr.rssi[1] + 321) / 2;
		wstats.noise = ai->wstats.qual.noise;
		wstats.updated =  IW_QUAL_LEVEL_UPDATED
				| IW_QUAL_QUAL_UPDATED
				| IW_QUAL_DBM;
		/* Update spy records */
		wireless_spy_update(ai->dev, sa, &wstats);
	}
#endif /* WIRELESS_SPY */

done:
	OUT4500(ai, EVACK, EV_RX);

	if (success) {
		if (test_bit(FLAG_802_11, &ai->flags)) {
			skb_reset_mac_header(skb);
			skb->pkt_type = PACKET_OTHERHOST;
			skb->dev = ai->wifidev;
			skb->protocol = htons(ETH_P_802_2);
		} else
			skb->protocol = eth_type_trans(skb, ai->dev);
		skb->ip_summed = CHECKSUM_NONE;

		netif_rx(skb);
	}
}