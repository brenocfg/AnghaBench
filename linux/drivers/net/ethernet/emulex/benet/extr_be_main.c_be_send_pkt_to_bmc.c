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
typedef  scalar_t__ u8 ;
struct udphdr {int /*<<< orphan*/  dest; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;
struct icmp6hdr {int icmp6_type; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
#define  DHCPV6_RAS_PORT 134 
#define  DHCP_CLIENT_PORT 133 
#define  DHCP_SERVER_PORT 132 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
#define  NDISC_NEIGHBOUR_ADVERTISEMENT 131 
#define  NDISC_ROUTER_ADVERTISEMENT 130 
#define  NET_BIOS_PORT1 129 
#define  NET_BIOS_PORT2 128 
 struct sk_buff* be_insert_vlan_in_pkt (struct be_adapter*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_is_os2bmc_enabled (struct be_adapter*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct icmp6hdr* icmp6_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ is_arp_allowed_on_bmc (struct be_adapter*,struct sk_buff*) ; 
 scalar_t__ is_bc_allowed_on_bmc (struct be_adapter*,struct ethhdr*) ; 
 int is_dhcp_client_filt_enabled (struct be_adapter*) ; 
 int is_dhcp_srvr_filt_enabled (struct be_adapter*) ; 
 int is_ipv6_na_filt_enabled (struct be_adapter*) ; 
 int is_ipv6_ra_filt_enabled (struct be_adapter*) ; 
 int is_ipv6_ras_filt_enabled (struct be_adapter*) ; 
 scalar_t__ is_mc_allowed_on_bmc (struct be_adapter*,struct ethhdr*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int is_nbios_filt_enabled (struct be_adapter*) ; 
 scalar_t__ is_udp_pkt (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static bool be_send_pkt_to_bmc(struct be_adapter *adapter,
			       struct sk_buff **skb)
{
	struct ethhdr *eh = (struct ethhdr *)(*skb)->data;
	bool os2bmc = false;

	if (!be_is_os2bmc_enabled(adapter))
		goto done;

	if (!is_multicast_ether_addr(eh->h_dest))
		goto done;

	if (is_mc_allowed_on_bmc(adapter, eh) ||
	    is_bc_allowed_on_bmc(adapter, eh) ||
	    is_arp_allowed_on_bmc(adapter, (*skb))) {
		os2bmc = true;
		goto done;
	}

	if ((*skb)->protocol == htons(ETH_P_IPV6)) {
		struct ipv6hdr *hdr = ipv6_hdr((*skb));
		u8 nexthdr = hdr->nexthdr;

		if (nexthdr == IPPROTO_ICMPV6) {
			struct icmp6hdr *icmp6 = icmp6_hdr((*skb));

			switch (icmp6->icmp6_type) {
			case NDISC_ROUTER_ADVERTISEMENT:
				os2bmc = is_ipv6_ra_filt_enabled(adapter);
				goto done;
			case NDISC_NEIGHBOUR_ADVERTISEMENT:
				os2bmc = is_ipv6_na_filt_enabled(adapter);
				goto done;
			default:
				break;
			}
		}
	}

	if (is_udp_pkt((*skb))) {
		struct udphdr *udp = udp_hdr((*skb));

		switch (ntohs(udp->dest)) {
		case DHCP_CLIENT_PORT:
			os2bmc = is_dhcp_client_filt_enabled(adapter);
			goto done;
		case DHCP_SERVER_PORT:
			os2bmc = is_dhcp_srvr_filt_enabled(adapter);
			goto done;
		case NET_BIOS_PORT1:
		case NET_BIOS_PORT2:
			os2bmc = is_nbios_filt_enabled(adapter);
			goto done;
		case DHCPV6_RAS_PORT:
			os2bmc = is_ipv6_ras_filt_enabled(adapter);
			goto done;
		default:
			break;
		}
	}
done:
	/* For packets over a vlan, which are destined
	 * to BMC, asic expects the vlan to be inline in the packet.
	 */
	if (os2bmc)
		*skb = be_insert_vlan_in_pkt(adapter, *skb, NULL);

	return os2bmc;
}