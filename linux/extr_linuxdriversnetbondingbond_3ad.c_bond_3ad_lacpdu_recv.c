#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct slave {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  len; } ;
struct lacpdu {int dummy; } ;
struct bonding {int dummy; } ;
typedef  int /*<<< orphan*/  _lacpdu ;
struct TYPE_2__ {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDRESS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_TYPE_LACPDU ; 
 int RX_HANDLER_ANOTHER ; 
 int bond_3ad_rx_indication (struct lacpdu*,struct slave*,int /*<<< orphan*/ ) ; 
 TYPE_1__* eth_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  lacpdu_mcast_addr ; 
 struct lacpdu* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct lacpdu*) ; 

int bond_3ad_lacpdu_recv(const struct sk_buff *skb, struct bonding *bond,
			 struct slave *slave)
{
	struct lacpdu *lacpdu, _lacpdu;

	if (skb->protocol != PKT_TYPE_LACPDU)
		return RX_HANDLER_ANOTHER;

	if (!MAC_ADDRESS_EQUAL(eth_hdr(skb)->h_dest, lacpdu_mcast_addr))
		return RX_HANDLER_ANOTHER;

	lacpdu = skb_header_pointer(skb, 0, sizeof(_lacpdu), &_lacpdu);
	if (!lacpdu)
		return RX_HANDLER_ANOTHER;

	return bond_3ad_rx_indication(lacpdu, slave, skb->len);
}