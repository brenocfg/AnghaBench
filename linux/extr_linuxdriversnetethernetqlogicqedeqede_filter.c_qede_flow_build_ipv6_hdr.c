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
struct udphdr {int dummy; } ;
struct tcphdr {int dummy; } ;
struct qede_arfs_tuple {scalar_t__ ip_proto; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; int /*<<< orphan*/  eth_proto; } ;
struct ipv6hdr {int version; void* payload_len; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct in6_addr {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ETH_HLEN ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  NEXTHDR_TCP ; 
 int /*<<< orphan*/  NEXTHDR_UDP ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qede_flow_build_ipv6_hdr(struct qede_arfs_tuple *t,
				     void *header)
{
	__be16 *ports = (__be16 *)(header + ETH_HLEN + sizeof(struct ipv6hdr));
	struct ipv6hdr *ip6 = (struct ipv6hdr *)(header + ETH_HLEN);
	struct ethhdr *eth = (struct ethhdr *)header;

	eth->h_proto = t->eth_proto;
	memcpy(&ip6->saddr, &t->src_ipv6, sizeof(struct in6_addr));
	memcpy(&ip6->daddr, &t->dst_ipv6, sizeof(struct in6_addr));
	ip6->version = 0x6;

	if (t->ip_proto == IPPROTO_TCP) {
		ip6->nexthdr = NEXTHDR_TCP;
		ip6->payload_len = cpu_to_be16(sizeof(struct tcphdr));
	} else {
		ip6->nexthdr = NEXTHDR_UDP;
		ip6->payload_len = cpu_to_be16(sizeof(struct udphdr));
	}

	/* ports is weakly typed to suit both TCP and UDP ports */
	ports[0] = t->src_port;
	ports[1] = t->dst_port;
}