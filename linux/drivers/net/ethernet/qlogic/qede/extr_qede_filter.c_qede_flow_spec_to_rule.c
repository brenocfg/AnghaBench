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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int dummy; } ;
struct ethtool_rx_flow_spec_input {struct ethtool_rx_flow_spec* fs; } ;
struct ethtool_rx_flow_spec {int flow_type; int /*<<< orphan*/  location; } ;
struct ethtool_rx_flow_rule {TYPE_1__* rule; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int FLOW_EXT ; 
 scalar_t__ IS_ERR (struct ethtool_rx_flow_rule*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int PTR_ERR (struct ethtool_rx_flow_rule*) ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 struct ethtool_rx_flow_rule* ethtool_rx_flow_rule_create (struct ethtool_rx_flow_spec_input*) ; 
 int /*<<< orphan*/  ethtool_rx_flow_rule_destroy (struct ethtool_rx_flow_rule*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int qede_flow_spec_validate (struct qede_dev*,int /*<<< orphan*/ *,struct qede_arfs_tuple*,int /*<<< orphan*/ ) ; 
 scalar_t__ qede_flow_spec_validate_unused (struct qede_dev*,struct ethtool_rx_flow_spec*) ; 
 scalar_t__ qede_parse_flow_attr (struct qede_dev*,int /*<<< orphan*/ ,TYPE_1__*,struct qede_arfs_tuple*) ; 

__attribute__((used)) static int qede_flow_spec_to_rule(struct qede_dev *edev,
				  struct qede_arfs_tuple *t,
				  struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_rx_flow_spec_input input = {};
	struct ethtool_rx_flow_rule *flow;
	__be16 proto;
	int err = 0;

	if (qede_flow_spec_validate_unused(edev, fs))
		return -EOPNOTSUPP;

	switch ((fs->flow_type & ~FLOW_EXT)) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
		proto = htons(ETH_P_IP);
		break;
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
		proto = htons(ETH_P_IPV6);
		break;
	default:
		DP_VERBOSE(edev, NETIF_MSG_IFUP,
			   "Can't support flow of type %08x\n", fs->flow_type);
		return -EOPNOTSUPP;
	}

	input.fs = fs;
	flow = ethtool_rx_flow_rule_create(&input);
	if (IS_ERR(flow))
		return PTR_ERR(flow);

	if (qede_parse_flow_attr(edev, proto, flow->rule, t)) {
		err = -EINVAL;
		goto err_out;
	}

	/* Make sure location is valid and filter isn't already set */
	err = qede_flow_spec_validate(edev, &flow->rule->action, t,
				      fs->location);
err_out:
	ethtool_rx_flow_rule_destroy(flow);
	return err;

}