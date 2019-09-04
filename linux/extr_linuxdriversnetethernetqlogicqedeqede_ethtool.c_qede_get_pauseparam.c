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
struct qed_link_output {int pause_config; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  current_link ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_output*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int QED_LINK_PAUSE_AUTONEG_ENABLE ; 
 int QED_LINK_PAUSE_RX_ENABLE ; 
 int QED_LINK_PAUSE_TX_ENABLE ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int /*<<< orphan*/  memset (struct qed_link_output*,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_link_output*) ; 

__attribute__((used)) static void qede_get_pauseparam(struct net_device *dev,
				struct ethtool_pauseparam *epause)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct qed_link_output current_link;

	memset(&current_link, 0, sizeof(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	if (current_link.pause_config & QED_LINK_PAUSE_AUTONEG_ENABLE)
		epause->autoneg = true;
	if (current_link.pause_config & QED_LINK_PAUSE_RX_ENABLE)
		epause->rx_pause = true;
	if (current_link.pause_config & QED_LINK_PAUSE_TX_ENABLE)
		epause->tx_pause = true;

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "ethtool_pauseparam: cmd %d  autoneg %d  rx_pause %d  tx_pause %d\n",
		   epause->cmd, epause->autoneg, epause->rx_pause,
		   epause->tx_pause);
}