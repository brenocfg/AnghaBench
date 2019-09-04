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
typedef  int /*<<< orphan*/  u32 ;
struct qede_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; int /*<<< orphan*/  rule_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int /*<<< orphan*/  QEDE_RFS_MAX_FLTR ; 
 int /*<<< orphan*/  QEDE_RSS_COUNT (struct qede_dev*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_get_arfs_filter_count (struct qede_dev*) ; 
 int qede_get_cls_rule_all (struct qede_dev*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int qede_get_cls_rule_entry (struct qede_dev*,struct ethtool_rxnfc*) ; 
 int qede_get_rss_flags (struct qede_dev*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int qede_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info,
			  u32 *rule_locs)
{
	struct qede_dev *edev = netdev_priv(dev);
	int rc = 0;

	switch (info->cmd) {
	case ETHTOOL_GRXRINGS:
		info->data = QEDE_RSS_COUNT(edev);
		break;
	case ETHTOOL_GRXFH:
		rc = qede_get_rss_flags(edev, info);
		break;
	case ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt = qede_get_arfs_filter_count(edev);
		info->data = QEDE_RFS_MAX_FLTR;
		break;
	case ETHTOOL_GRXCLSRULE:
		rc = qede_get_cls_rule_entry(edev, info);
		break;
	case ETHTOOL_GRXCLSRLALL:
		rc = qede_get_cls_rule_all(edev, info, rule_locs);
		break;
	default:
		DP_ERR(edev, "Command parameters not supported\n");
		rc = -EOPNOTSUPP;
	}

	return rc;
}