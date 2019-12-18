#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  protocol; scalar_t__ len; } ;
struct brcmf_if {TYPE_2__* ndev; TYPE_4__* drvr; } ;
struct TYPE_8__ {TYPE_3__* settings; } ;
struct TYPE_7__ {int /*<<< orphan*/  iapp; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  multicast; } ;
struct TYPE_6__ {int flags; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int IFF_UP ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_skb_is_iapp (struct sk_buff*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void brcmf_netif_rx(struct brcmf_if *ifp, struct sk_buff *skb)
{
	/* Most of Broadcom's firmwares send 802.11f ADD frame every time a new
	 * STA connects to the AP interface. This is an obsoleted standard most
	 * users don't use, so don't pass these frames up unless requested.
	 */
	if (!ifp->drvr->settings->iapp && brcmf_skb_is_iapp(skb)) {
		brcmu_pkt_buf_free_skb(skb);
		return;
	}

	if (skb->pkt_type == PACKET_MULTICAST)
		ifp->ndev->stats.multicast++;

	if (!(ifp->ndev->flags & IFF_UP)) {
		brcmu_pkt_buf_free_skb(skb);
		return;
	}

	ifp->ndev->stats.rx_bytes += skb->len;
	ifp->ndev->stats.rx_packets++;

	brcmf_dbg(DATA, "rx proto=0x%X\n", ntohs(skb->protocol));
	if (in_interrupt())
		netif_rx(skb);
	else
		/* If the receive is not processed inside an ISR,
		 * the softirqd must be woken explicitly to service
		 * the NET_RX_SOFTIRQ.  This is handled by netif_rx_ni().
		 */
		netif_rx_ni(skb);
}