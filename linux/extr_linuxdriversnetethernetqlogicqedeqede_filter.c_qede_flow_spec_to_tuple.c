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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int dummy; } ;
struct ethtool_rx_flow_spec {int flow_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EOPNOTSUPP ; 
 int FLOW_EXT ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  memset (struct qede_arfs_tuple*,int /*<<< orphan*/ ,int) ; 
 int qede_flow_spec_to_tuple_tcpv4 (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 
 int qede_flow_spec_to_tuple_tcpv6 (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 
 int qede_flow_spec_to_tuple_udpv4 (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 
 int qede_flow_spec_to_tuple_udpv6 (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 
 scalar_t__ qede_flow_spec_validate_unused (struct qede_dev*,struct ethtool_rx_flow_spec*) ; 

__attribute__((used)) static int qede_flow_spec_to_tuple(struct qede_dev *edev,
				   struct qede_arfs_tuple *t,
				   struct ethtool_rx_flow_spec *fs)
{
	memset(t, 0, sizeof(*t));

	if (qede_flow_spec_validate_unused(edev, fs))
		return -EOPNOTSUPP;

	switch ((fs->flow_type & ~FLOW_EXT)) {
	case TCP_V4_FLOW:
		return qede_flow_spec_to_tuple_tcpv4(edev, t, fs);
	case UDP_V4_FLOW:
		return qede_flow_spec_to_tuple_udpv4(edev, t, fs);
	case TCP_V6_FLOW:
		return qede_flow_spec_to_tuple_tcpv6(edev, t, fs);
	case UDP_V6_FLOW:
		return qede_flow_spec_to_tuple_udpv6(edev, t, fs);
	default:
		DP_VERBOSE(edev, NETIF_MSG_IFUP,
			   "Can't support flow of type %08x\n", fs->flow_type);
		return -EOPNOTSUPP;
	}

	return 0;
}