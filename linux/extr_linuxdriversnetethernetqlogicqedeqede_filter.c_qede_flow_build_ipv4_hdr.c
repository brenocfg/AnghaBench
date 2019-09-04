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
struct qede_arfs_tuple {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/  src_ipv4; int /*<<< orphan*/  eth_proto; } ;
struct iphdr {int version; int ihl; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int qede_flow_get_min_header_size (struct qede_arfs_tuple*) ; 

__attribute__((used)) static void qede_flow_build_ipv4_hdr(struct qede_arfs_tuple *t,
				     void *header)
{
	__be16 *ports = (__be16 *)(header + ETH_HLEN + sizeof(struct iphdr));
	struct iphdr *ip = (struct iphdr *)(header + ETH_HLEN);
	struct ethhdr *eth = (struct ethhdr *)header;

	eth->h_proto = t->eth_proto;
	ip->saddr = t->src_ipv4;
	ip->daddr = t->dst_ipv4;
	ip->version = 0x4;
	ip->ihl = 0x5;
	ip->protocol = t->ip_proto;
	ip->tot_len = cpu_to_be16(qede_flow_get_min_header_size(t) - ETH_HLEN);

	/* ports is weakly typed to suit both TCP and UDP ports */
	ports[0] = t->src_port;
	ports[1] = t->dst_port;
}