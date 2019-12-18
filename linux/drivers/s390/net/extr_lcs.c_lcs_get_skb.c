#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ protocol; scalar_t__ cb; } ;
struct TYPE_3__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct lcs_card {scalar_t__ state; scalar_t__ (* lan_type_trans ) (struct sk_buff*,TYPE_2__*) ;scalar_t__ pkt_seq; TYPE_1__ stats; TYPE_2__* dev; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_UP ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,char*,unsigned int) ; 
 scalar_t__ stub1 (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
lcs_get_skb(struct lcs_card *card, char *skb_data, unsigned int skb_len)
{
	struct sk_buff *skb;

	LCS_DBF_TEXT(5, trace, "getskb");
	if (card->dev == NULL ||
	    card->state != DEV_STATE_UP)
		/* The card isn't up. Ignore the packet. */
		return;

	skb = dev_alloc_skb(skb_len);
	if (skb == NULL) {
		dev_err(&card->dev->dev,
			" Allocating a socket buffer to interface %s failed\n",
			  card->dev->name);
		card->stats.rx_dropped++;
		return;
	}
	skb_put_data(skb, skb_data, skb_len);
	skb->protocol =	card->lan_type_trans(skb, card->dev);
	card->stats.rx_bytes += skb_len;
	card->stats.rx_packets++;
	if (skb->protocol == htons(ETH_P_802_2))
		*((__u32 *)skb->cb) = ++card->pkt_seq;
	netif_rx(skb);
}