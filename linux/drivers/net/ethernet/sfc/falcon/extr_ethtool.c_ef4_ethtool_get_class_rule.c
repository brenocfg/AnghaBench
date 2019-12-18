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
struct ethtool_usrip6_spec {scalar_t__ l4_proto; int /*<<< orphan*/  ip6src; int /*<<< orphan*/  ip6dst; } ;
struct ethtool_usrip4_spec {scalar_t__ proto; void* ip4src; void* ip4dst; int /*<<< orphan*/  ip_ver; } ;
struct ethtool_tcpip6_spec {void* psrc; void* pdst; int /*<<< orphan*/  ip6src; int /*<<< orphan*/  ip6dst; } ;
struct ethtool_tcpip4_spec {void* psrc; void* pdst; void* ip4src; void* ip4dst; } ;
struct TYPE_6__ {scalar_t__ vlan_tci; } ;
struct TYPE_5__ {int /*<<< orphan*/  vlan_tci; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
struct TYPE_8__ {struct ethhdr ether_spec; struct ethtool_usrip6_spec usr_ip6_spec; struct ethtool_tcpip6_spec tcp_ip6_spec; struct ethtool_usrip4_spec usr_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_7__ {struct ethhdr ether_spec; struct ethtool_usrip6_spec usr_ip6_spec; struct ethtool_tcpip6_spec tcp_ip6_spec; struct ethtool_usrip4_spec usr_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {scalar_t__ ring_cookie; TYPE_2__ m_ext; TYPE_1__ h_ext; int /*<<< orphan*/  flow_type; int /*<<< orphan*/  location; TYPE_4__ m_u; TYPE_3__ h_u; } ;
struct ef4_nic {int dummy; } ;
struct ef4_filter_spec {scalar_t__ dmaq_id; int match_flags; scalar_t__ ether_type; scalar_t__ ip_proto; int /*<<< orphan*/  outer_vid; void** rem_host; void** loc_host; int /*<<< orphan*/  rem_mac; int /*<<< orphan*/  loc_mac; void* rem_port; void* loc_port; } ;

/* Variables and functions */
 int EF4_FILTER_MATCH_ETHER_TYPE ; 
 int EF4_FILTER_MATCH_IP_PROTO ; 
 int EF4_FILTER_MATCH_LOC_HOST ; 
 int EF4_FILTER_MATCH_LOC_MAC ; 
 int EF4_FILTER_MATCH_LOC_MAC_IG ; 
 int EF4_FILTER_MATCH_LOC_PORT ; 
 int EF4_FILTER_MATCH_OUTER_VID ; 
 int EF4_FILTER_MATCH_REM_HOST ; 
 int EF4_FILTER_MATCH_REM_MAC ; 
 int EF4_FILTER_MATCH_REM_PORT ; 
 int /*<<< orphan*/  EF4_FILTER_PRI_MANUAL ; 
 scalar_t__ EF4_FILTER_RX_DMAQ_ID_DROP ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHER_FLOW ; 
 scalar_t__ ETHER_TYPE_FULL_MASK ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_RX_NFC_IP4 ; 
 int /*<<< orphan*/  FLOW_EXT ; 
 void* IP4_ADDR_FULL_MASK ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  IPV4_USER_FLOW ; 
 int /*<<< orphan*/  IPV6_USER_FLOW ; 
 void* IP_PROTO_FULL_MASK ; 
 void* PORT_FULL_MASK ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
 int /*<<< orphan*/  TCP_V4_FLOW ; 
 int /*<<< orphan*/  TCP_V6_FLOW ; 
 int /*<<< orphan*/  UDP_V4_FLOW ; 
 int /*<<< orphan*/  UDP_V6_FLOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ef4_filter_get_filter_safe (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ef4_filter_spec*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  ip6_fill_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_addr_ig_mask ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static int ef4_ethtool_get_class_rule(struct ef4_nic *efx,
				      struct ethtool_rx_flow_spec *rule)
{
	struct ethtool_tcpip4_spec *ip_entry = &rule->h_u.tcp_ip4_spec;
	struct ethtool_tcpip4_spec *ip_mask = &rule->m_u.tcp_ip4_spec;
	struct ethtool_usrip4_spec *uip_entry = &rule->h_u.usr_ip4_spec;
	struct ethtool_usrip4_spec *uip_mask = &rule->m_u.usr_ip4_spec;
	struct ethtool_tcpip6_spec *ip6_entry = &rule->h_u.tcp_ip6_spec;
	struct ethtool_tcpip6_spec *ip6_mask = &rule->m_u.tcp_ip6_spec;
	struct ethtool_usrip6_spec *uip6_entry = &rule->h_u.usr_ip6_spec;
	struct ethtool_usrip6_spec *uip6_mask = &rule->m_u.usr_ip6_spec;
	struct ethhdr *mac_entry = &rule->h_u.ether_spec;
	struct ethhdr *mac_mask = &rule->m_u.ether_spec;
	struct ef4_filter_spec spec;
	int rc;

	rc = ef4_filter_get_filter_safe(efx, EF4_FILTER_PRI_MANUAL,
					rule->location, &spec);
	if (rc)
		return rc;

	if (spec.dmaq_id == EF4_FILTER_RX_DMAQ_ID_DROP)
		rule->ring_cookie = RX_CLS_FLOW_DISC;
	else
		rule->ring_cookie = spec.dmaq_id;

	if ((spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IP) &&
	    (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_PORT | EF4_FILTER_MATCH_REM_PORT))) {
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V4_FLOW : UDP_V4_FLOW);
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) {
			ip_entry->ip4dst = spec.loc_host[0];
			ip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) {
			ip_entry->ip4src = spec.rem_host[0];
			ip_mask->ip4src = IP4_ADDR_FULL_MASK;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_PORT) {
			ip_entry->pdst = spec.loc_port;
			ip_mask->pdst = PORT_FULL_MASK;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_PORT) {
			ip_entry->psrc = spec.rem_port;
			ip_mask->psrc = PORT_FULL_MASK;
		}
	} else if ((spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IPV6) &&
	    (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_PORT | EF4_FILTER_MATCH_REM_PORT))) {
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V6_FLOW : UDP_V6_FLOW);
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) {
			memcpy(ip6_entry->ip6dst, spec.loc_host,
			       sizeof(ip6_entry->ip6dst));
			ip6_fill_mask(ip6_mask->ip6dst);
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) {
			memcpy(ip6_entry->ip6src, spec.rem_host,
			       sizeof(ip6_entry->ip6src));
			ip6_fill_mask(ip6_mask->ip6src);
		}
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_PORT) {
			ip6_entry->pdst = spec.loc_port;
			ip6_mask->pdst = PORT_FULL_MASK;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_PORT) {
			ip6_entry->psrc = spec.rem_port;
			ip6_mask->psrc = PORT_FULL_MASK;
		}
	} else if (!(spec.match_flags &
		     ~(EF4_FILTER_MATCH_LOC_MAC | EF4_FILTER_MATCH_LOC_MAC_IG |
		       EF4_FILTER_MATCH_REM_MAC | EF4_FILTER_MATCH_ETHER_TYPE |
		       EF4_FILTER_MATCH_OUTER_VID))) {
		rule->flow_type = ETHER_FLOW;
		if (spec.match_flags &
		    (EF4_FILTER_MATCH_LOC_MAC | EF4_FILTER_MATCH_LOC_MAC_IG)) {
			ether_addr_copy(mac_entry->h_dest, spec.loc_mac);
			if (spec.match_flags & EF4_FILTER_MATCH_LOC_MAC)
				eth_broadcast_addr(mac_mask->h_dest);
			else
				ether_addr_copy(mac_mask->h_dest,
						mac_addr_ig_mask);
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_MAC) {
			ether_addr_copy(mac_entry->h_source, spec.rem_mac);
			eth_broadcast_addr(mac_mask->h_source);
		}
		if (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) {
			mac_entry->h_proto = spec.ether_type;
			mac_mask->h_proto = ETHER_TYPE_FULL_MASK;
		}
	} else if (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IP) &&
		   !(spec.match_flags &
		     ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		       EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		       EF4_FILTER_MATCH_IP_PROTO))) {
		rule->flow_type = IPV4_USER_FLOW;
		uip_entry->ip_ver = ETH_RX_NFC_IP4;
		if (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) {
			uip_mask->proto = IP_PROTO_FULL_MASK;
			uip_entry->proto = spec.ip_proto;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) {
			uip_entry->ip4dst = spec.loc_host[0];
			uip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) {
			uip_entry->ip4src = spec.rem_host[0];
			uip_mask->ip4src = IP4_ADDR_FULL_MASK;
		}
	} else if (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IPV6) &&
		   !(spec.match_flags &
		     ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		       EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		       EF4_FILTER_MATCH_IP_PROTO))) {
		rule->flow_type = IPV6_USER_FLOW;
		if (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) {
			uip6_mask->l4_proto = IP_PROTO_FULL_MASK;
			uip6_entry->l4_proto = spec.ip_proto;
		}
		if (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) {
			memcpy(uip6_entry->ip6dst, spec.loc_host,
			       sizeof(uip6_entry->ip6dst));
			ip6_fill_mask(uip6_mask->ip6dst);
		}
		if (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) {
			memcpy(uip6_entry->ip6src, spec.rem_host,
			       sizeof(uip6_entry->ip6src));
			ip6_fill_mask(uip6_mask->ip6src);
		}
	} else {
		/* The above should handle all filters that we insert */
		WARN_ON(1);
		return -EINVAL;
	}

	if (spec.match_flags & EF4_FILTER_MATCH_OUTER_VID) {
		rule->flow_type |= FLOW_EXT;
		rule->h_ext.vlan_tci = spec.outer_vid;
		rule->m_ext.vlan_tci = htons(0xfff);
	}

	return rc;
}