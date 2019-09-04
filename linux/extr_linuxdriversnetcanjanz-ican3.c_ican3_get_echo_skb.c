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
typedef  unsigned int u8 ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct ican3_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  echoq; } ;
struct can_frame {unsigned int can_dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_CAN ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_LOOPBACK ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ican3_get_echo_skb(struct ican3_dev *mod)
{
	struct sk_buff *skb = skb_dequeue(&mod->echoq);
	struct can_frame *cf;
	u8 dlc;

	/* this should never trigger unless there is a driver bug */
	if (!skb) {
		netdev_err(mod->ndev, "BUG: echo skb not occupied\n");
		return 0;
	}

	cf = (struct can_frame *)skb->data;
	dlc = cf->can_dlc;

	/* check flag whether this packet has to be looped back */
	if (skb->pkt_type != PACKET_LOOPBACK) {
		kfree_skb(skb);
		return dlc;
	}

	skb->protocol = htons(ETH_P_CAN);
	skb->pkt_type = PACKET_BROADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->dev = mod->ndev;
	netif_receive_skb(skb);
	return dlc;
}