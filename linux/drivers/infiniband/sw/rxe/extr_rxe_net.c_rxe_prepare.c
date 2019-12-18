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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ protocol; TYPE_1__* dev; } ;
struct rxe_pkt_info {int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmac; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  RXE_LOOPBACK_MASK ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int prepare4 (struct rxe_pkt_info*,struct sk_buff*) ; 
 int prepare6 (struct rxe_pkt_info*,struct sk_buff*) ; 
 TYPE_2__* rxe_get_av (struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  rxe_icrc_hdr (struct rxe_pkt_info*,struct sk_buff*) ; 

int rxe_prepare(struct rxe_pkt_info *pkt, struct sk_buff *skb, u32 *crc)
{
	int err = 0;

	if (skb->protocol == htons(ETH_P_IP))
		err = prepare4(pkt, skb);
	else if (skb->protocol == htons(ETH_P_IPV6))
		err = prepare6(pkt, skb);

	*crc = rxe_icrc_hdr(pkt, skb);

	if (ether_addr_equal(skb->dev->dev_addr, rxe_get_av(pkt)->dmac))
		pkt->mask |= RXE_LOOPBACK_MASK;

	return err;
}