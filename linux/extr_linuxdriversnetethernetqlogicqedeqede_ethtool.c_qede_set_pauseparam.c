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
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct qed_link_params {int supported_caps; int link_up; int /*<<< orphan*/  pause_config; int /*<<< orphan*/  override_flags; } ;
struct qed_link_output {int supported_caps; int link_up; int /*<<< orphan*/  pause_config; int /*<<< orphan*/  override_flags; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; scalar_t__ autoneg; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  current_link ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* can_link_change ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QED_LINK_OVERRIDE_PAUSE_CONFIG ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_AUTONEG_ENABLE ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_RX_ENABLE ; 
 int /*<<< orphan*/  QED_LINK_PAUSE_TX_ENABLE ; 
 int QED_LM_Autoneg_BIT ; 
 int /*<<< orphan*/  memset (struct qed_link_params*,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qed_link_params*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qed_link_params*) ; 

__attribute__((used)) static int qede_set_pauseparam(struct net_device *dev,
			       struct ethtool_pauseparam *epause)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct qed_link_params params;
	struct qed_link_output current_link;

	if (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) {
		DP_INFO(edev,
			"Pause settings are not allowed to be changed\n");
		return -EOPNOTSUPP;
	}

	memset(&current_link, 0, sizeof(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	memset(&params, 0, sizeof(params));
	params.override_flags |= QED_LINK_OVERRIDE_PAUSE_CONFIG;
	if (epause->autoneg) {
		if (!(current_link.supported_caps & QED_LM_Autoneg_BIT)) {
			DP_INFO(edev, "autoneg not supported\n");
			return -EINVAL;
		}
		params.pause_config |= QED_LINK_PAUSE_AUTONEG_ENABLE;
	}
	if (epause->rx_pause)
		params.pause_config |= QED_LINK_PAUSE_RX_ENABLE;
	if (epause->tx_pause)
		params.pause_config |= QED_LINK_PAUSE_TX_ENABLE;

	params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &params);

	return 0;
}