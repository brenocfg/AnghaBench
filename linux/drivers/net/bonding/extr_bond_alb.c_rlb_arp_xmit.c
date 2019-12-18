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
struct slave {TYPE_2__* dev; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rlb_update_delay_counter; } ;
struct bonding {int /*<<< orphan*/  dev; TYPE_1__ alb_info; } ;
struct arp_pkt {scalar_t__ op_code; int /*<<< orphan*/  ip_src; int /*<<< orphan*/  mac_src; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  RLB_UPDATE_DELAY ; 
 struct arp_pkt* arp_pkt (struct sk_buff*) ; 
 int /*<<< orphan*/  bond_hw_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_slave_has_mac_rx (struct bonding*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 struct slave* rlb_choose_channel (struct sk_buff*,struct bonding*) ; 
 int /*<<< orphan*/  rlb_req_update_subnet_clients (struct bonding*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct slave *rlb_arp_xmit(struct sk_buff *skb, struct bonding *bond)
{
	struct arp_pkt *arp = arp_pkt(skb);
	struct slave *tx_slave = NULL;

	/* Don't modify or load balance ARPs that do not originate locally
	 * (e.g.,arrive via a bridge).
	 */
	if (!bond_slave_has_mac_rx(bond, arp->mac_src))
		return NULL;

	if (arp->op_code == htons(ARPOP_REPLY)) {
		/* the arp must be sent on the selected rx channel */
		tx_slave = rlb_choose_channel(skb, bond);
		if (tx_slave)
			bond_hw_addr_copy(arp->mac_src, tx_slave->dev->dev_addr,
					  tx_slave->dev->addr_len);
		netdev_dbg(bond->dev, "(slave %s): Server sent ARP Reply packet\n",
			   tx_slave ? tx_slave->dev->name : "NULL");
	} else if (arp->op_code == htons(ARPOP_REQUEST)) {
		/* Create an entry in the rx_hashtbl for this client as a
		 * place holder.
		 * When the arp reply is received the entry will be updated
		 * with the correct unicast address of the client.
		 */
		tx_slave = rlb_choose_channel(skb, bond);

		/* The ARP reply packets must be delayed so that
		 * they can cancel out the influence of the ARP request.
		 */
		bond->alb_info.rlb_update_delay_counter = RLB_UPDATE_DELAY;

		/* arp requests are broadcast and are sent on the primary
		 * the arp request will collapse all clients on the subnet to
		 * the primary slave. We must register these clients to be
		 * updated with their assigned mac.
		 */
		rlb_req_update_subnet_clients(bond, arp->ip_src);
		netdev_dbg(bond->dev, "(slave %s): Server sent ARP Request packet\n",
			   tx_slave ? tx_slave->dev->name : "NULL");
	}

	return tx_slave;
}