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
typedef  int /*<<< orphan*/  zero_addr ;
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int src_port; int dst_port; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; int /*<<< orphan*/  eth_proto; } ;
struct in6_addr {int dummy; } ;
struct TYPE_7__ {int psrc; int pdst; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; scalar_t__ tclass; } ;
struct TYPE_8__ {TYPE_3__ tcp_ip6_spec; } ;
struct TYPE_5__ {int psrc; int pdst; } ;
struct TYPE_6__ {TYPE_1__ tcp_ip6_spec; } ;
struct ethtool_rx_flow_spec {TYPE_4__ h_u; TYPE_2__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 int qede_set_v6_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*,struct in6_addr*) ; 

__attribute__((used)) static int qede_flow_spec_to_tuple_ipv6_common(struct qede_dev *edev,
					       struct qede_arfs_tuple *t,
					       struct ethtool_rx_flow_spec *fs)
{
	struct in6_addr zero_addr;

	memset(&zero_addr, 0, sizeof(zero_addr));

	if ((fs->h_u.tcp_ip6_spec.psrc &
	     fs->m_u.tcp_ip6_spec.psrc) != fs->h_u.tcp_ip6_spec.psrc) {
		DP_INFO(edev, "Don't support port-masks\n");
		return -EOPNOTSUPP;
	}

	if ((fs->h_u.tcp_ip6_spec.pdst &
	     fs->m_u.tcp_ip6_spec.pdst) != fs->h_u.tcp_ip6_spec.pdst) {
		DP_INFO(edev, "Don't support port-masks\n");
		return -EOPNOTSUPP;
	}

	if (fs->h_u.tcp_ip6_spec.tclass) {
		DP_INFO(edev, "Don't support tclass\n");
		return -EOPNOTSUPP;
	}

	t->eth_proto = htons(ETH_P_IPV6);
	memcpy(&t->src_ipv6, &fs->h_u.tcp_ip6_spec.ip6src,
	       sizeof(struct in6_addr));
	memcpy(&t->dst_ipv6, &fs->h_u.tcp_ip6_spec.ip6dst,
	       sizeof(struct in6_addr));
	t->src_port = fs->h_u.tcp_ip6_spec.psrc;
	t->dst_port = fs->h_u.tcp_ip6_spec.pdst;

	return qede_set_v6_tuple_to_profile(edev, t, &zero_addr);
}