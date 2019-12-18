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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct ofdpa_port {int dummy; } ;
struct TYPE_3__ {int copy_to_cpu; void* vlan_id_mask; void* vlan_id; int /*<<< orphan*/  eth_dst_mask; int /*<<< orphan*/  eth_dst; void* eth_type; void* in_pport_mask; void* in_pport; int /*<<< orphan*/  goto_tbl; } ;
struct TYPE_4__ {TYPE_1__ term_mac; int /*<<< orphan*/  tbl_id; int /*<<< orphan*/  priority; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;
typedef  void* __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OFDPA_PRIORITY_TERM_MAC_MCAST ; 
 int /*<<< orphan*/  OFDPA_PRIORITY_TERM_MAC_UCAST ; 
 int /*<<< orphan*/  ROCKER_OF_DPA_TABLE_ID_MULTICAST_ROUTING ; 
 int /*<<< orphan*/  ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC ; 
 int /*<<< orphan*/  ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 struct ofdpa_flow_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_do (struct ofdpa_port*,int,struct ofdpa_flow_tbl_entry*) ; 

__attribute__((used)) static int ofdpa_flow_tbl_term_mac(struct ofdpa_port *ofdpa_port,
				   u32 in_pport, u32 in_pport_mask,
				   __be16 eth_type, const u8 *eth_dst,
				   const u8 *eth_dst_mask, __be16 vlan_id,
				   __be16 vlan_id_mask, bool copy_to_cpu,
				   int flags)
{
	struct ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	if (is_multicast_ether_addr(eth_dst)) {
		entry->key.priority = OFDPA_PRIORITY_TERM_MAC_MCAST;
		entry->key.term_mac.goto_tbl =
			 ROCKER_OF_DPA_TABLE_ID_MULTICAST_ROUTING;
	} else {
		entry->key.priority = OFDPA_PRIORITY_TERM_MAC_UCAST;
		entry->key.term_mac.goto_tbl =
			 ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING;
	}

	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC;
	entry->key.term_mac.in_pport = in_pport;
	entry->key.term_mac.in_pport_mask = in_pport_mask;
	entry->key.term_mac.eth_type = eth_type;
	ether_addr_copy(entry->key.term_mac.eth_dst, eth_dst);
	ether_addr_copy(entry->key.term_mac.eth_dst_mask, eth_dst_mask);
	entry->key.term_mac.vlan_id = vlan_id;
	entry->key.term_mac.vlan_id_mask = vlan_id_mask;
	entry->key.term_mac.copy_to_cpu = copy_to_cpu;

	return ofdpa_flow_tbl_do(ofdpa_port, flags, entry);
}