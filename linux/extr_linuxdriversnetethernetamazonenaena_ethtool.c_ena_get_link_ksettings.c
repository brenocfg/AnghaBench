#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct ena_com_dev {int dummy; } ;
struct ena_admin_get_feature_link_desc {int flags; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {struct ena_admin_get_feature_link_desc link; } ;
struct ena_admin_get_feat_resp {TYPE_1__ u; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK ; 
 int ena_com_get_link_params (struct ena_com_dev*,struct ena_admin_get_feat_resp*) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int ena_get_link_ksettings(struct net_device *netdev,
				  struct ethtool_link_ksettings *link_ksettings)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct ena_admin_get_feature_link_desc *link;
	struct ena_admin_get_feat_resp feat_resp;
	int rc;

	rc = ena_com_get_link_params(ena_dev, &feat_resp);
	if (rc)
		return rc;

	link = &feat_resp.u.link;
	link_ksettings->base.speed = link->speed;

	if (link->flags & ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK) {
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
	}

	link_ksettings->base.autoneg =
		(link->flags & ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	link_ksettings->base.duplex = DUPLEX_FULL;

	return 0;
}