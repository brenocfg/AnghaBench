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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int src_ipv4; int dst_ipv4; int src_port; int dst_port; int /*<<< orphan*/  eth_proto; } ;
struct TYPE_7__ {int ip4src; int ip4dst; int psrc; int pdst; scalar_t__ tos; } ;
struct TYPE_8__ {TYPE_3__ tcp_ip4_spec; } ;
struct TYPE_5__ {int ip4src; int ip4dst; int psrc; int pdst; } ;
struct TYPE_6__ {TYPE_1__ tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {TYPE_4__ h_u; TYPE_2__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int qede_set_v4_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*) ; 

__attribute__((used)) static int qede_flow_spec_to_tuple_ipv4_common(struct qede_dev *edev,
					       struct qede_arfs_tuple *t,
					       struct ethtool_rx_flow_spec *fs)
{
	if ((fs->h_u.tcp_ip4_spec.ip4src &
	     fs->m_u.tcp_ip4_spec.ip4src) != fs->h_u.tcp_ip4_spec.ip4src) {
		DP_INFO(edev, "Don't support IP-masks\n");
		return -EOPNOTSUPP;
	}

	if ((fs->h_u.tcp_ip4_spec.ip4dst &
	     fs->m_u.tcp_ip4_spec.ip4dst) != fs->h_u.tcp_ip4_spec.ip4dst) {
		DP_INFO(edev, "Don't support IP-masks\n");
		return -EOPNOTSUPP;
	}

	if ((fs->h_u.tcp_ip4_spec.psrc &
	     fs->m_u.tcp_ip4_spec.psrc) != fs->h_u.tcp_ip4_spec.psrc) {
		DP_INFO(edev, "Don't support port-masks\n");
		return -EOPNOTSUPP;
	}

	if ((fs->h_u.tcp_ip4_spec.pdst &
	     fs->m_u.tcp_ip4_spec.pdst) != fs->h_u.tcp_ip4_spec.pdst) {
		DP_INFO(edev, "Don't support port-masks\n");
		return -EOPNOTSUPP;
	}

	if (fs->h_u.tcp_ip4_spec.tos) {
		DP_INFO(edev, "Don't support tos\n");
		return -EOPNOTSUPP;
	}

	t->eth_proto = htons(ETH_P_IP);
	t->src_ipv4 = fs->h_u.tcp_ip4_spec.ip4src;
	t->dst_ipv4 = fs->h_u.tcp_ip4_spec.ip4dst;
	t->src_port = fs->h_u.tcp_ip4_spec.psrc;
	t->dst_port = fs->h_u.tcp_ip4_spec.pdst;

	return qede_set_v4_tuple_to_profile(edev, t);
}