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
struct slave {int /*<<< orphan*/  dev; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct bonding {int /*<<< orphan*/  dev; } ;
struct arp_pkt {scalar_t__ op_code; } ;
typedef  int /*<<< orphan*/  _arp ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int RX_HANDLER_ANOTHER ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlb_purge_src_ip (struct bonding*,struct arp_pkt*) ; 
 int /*<<< orphan*/  rlb_update_entry_from_arp (struct bonding*,struct arp_pkt*) ; 
 struct arp_pkt* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct arp_pkt*) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rlb_arp_recv(const struct sk_buff *skb, struct bonding *bond,
			struct slave *slave)
{
	struct arp_pkt *arp, _arp;

	if (skb->protocol != cpu_to_be16(ETH_P_ARP))
		goto out;

	arp = skb_header_pointer(skb, 0, sizeof(_arp), &_arp);
	if (!arp)
		goto out;

	/* We received an ARP from arp->ip_src.
	 * We might have used this IP address previously (on the bonding host
	 * itself or on a system that is bridged together with the bond).
	 * However, if arp->mac_src is different than what is stored in
	 * rx_hashtbl, some other host is now using the IP and we must prevent
	 * sending out client updates with this IP address and the old MAC
	 * address.
	 * Clean up all hash table entries that have this address as ip_src but
	 * have a different mac_src.
	 */
	rlb_purge_src_ip(bond, arp);

	if (arp->op_code == htons(ARPOP_REPLY)) {
		/* update rx hash table for this ARP */
		rlb_update_entry_from_arp(bond, arp);
		slave_dbg(bond->dev, slave->dev, "Server received an ARP Reply from client\n");
	}
out:
	return RX_HANDLER_ANOTHER;
}