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
struct in6_addr {int dummy; } ;
struct ethtool_usrip6_spec {scalar_t__ l4_proto; scalar_t__ ip6dst; scalar_t__ ip6src; scalar_t__ tclass; scalar_t__ l4_4_bytes; } ;
struct TYPE_2__ {struct ethtool_usrip6_spec usr_ip6_spec; } ;
struct ethtool_rx_flow_spec {TYPE_1__ m_u; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 

__attribute__((used)) static int validate_ip6(struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_usrip6_spec *l3_mask = &fs->m_u.usr_ip6_spec;
	int ntuples = 0;

	if (l3_mask->l4_4_bytes || l3_mask->tclass)
		return -EINVAL;
	if (!ipv6_addr_any((struct in6_addr *)l3_mask->ip6src))
		ntuples++;

	if (!ipv6_addr_any((struct in6_addr *)l3_mask->ip6dst))
		ntuples++;
	if (l3_mask->l4_proto)
		ntuples++;
	/* Flow is IPv6 */
	return ++ntuples;
}