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
struct hinic_rss_type {int ipv4; int ipv6; } ;
struct hinic_dev {int flags; int /*<<< orphan*/  rss_tmpl_idx; struct hinic_rss_type rss_type; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int HINIC_RSS_ENABLE ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int hinic_get_rss_type (struct hinic_dev*,int /*<<< orphan*/ ,struct hinic_rss_type*) ; 
 int hinic_set_rss_type (struct hinic_dev*,int /*<<< orphan*/ ,struct hinic_rss_type) ; 
 int set_l4_rss_hash_ops (struct ethtool_rxnfc*,struct hinic_rss_type*) ; 

__attribute__((used)) static int hinic_set_rss_hash_opts(struct hinic_dev *nic_dev,
				   struct ethtool_rxnfc *cmd)
{
	struct hinic_rss_type *rss_type = &nic_dev->rss_type;
	int err;

	if (!(nic_dev->flags & HINIC_RSS_ENABLE)) {
		cmd->data = 0;
		return -EOPNOTSUPP;
	}

	/* RSS does not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	if (cmd->data & ~(RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 |
		RXH_L4_B_2_3))
		return -EINVAL;

	/* We need at least the IP SRC and DEST fields for hashing */
	if (!(cmd->data & RXH_IP_SRC) || !(cmd->data & RXH_IP_DST))
		return -EINVAL;

	err = hinic_get_rss_type(nic_dev,
				 nic_dev->rss_tmpl_idx, rss_type);
	if (err)
		return -EFAULT;

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		err = set_l4_rss_hash_ops(cmd, rss_type);
		if (err)
			return err;
		break;
	case IPV4_FLOW:
		rss_type->ipv4 = 1;
		break;
	case IPV6_FLOW:
		rss_type->ipv6 = 1;
		break;
	default:
		return -EINVAL;
	}

	err = hinic_set_rss_type(nic_dev, nic_dev->rss_tmpl_idx,
				 *rss_type);
	if (err)
		return -EFAULT;

	return 0;
}