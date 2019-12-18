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
struct TYPE_5__ {int /*<<< orphan*/  wol_support; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
struct qede_dev {int wol_enabled; int /*<<< orphan*/  cdev; TYPE_4__* ops; TYPE_2__ dev_info; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_8__ {TYPE_3__* common; } ;
struct TYPE_7__ {int (* update_wol ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int WAKE_MAGIC ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qede_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct qede_dev *edev = netdev_priv(ndev);
	bool wol_requested;
	int rc;

	if (wol->wolopts & ~WAKE_MAGIC) {
		DP_INFO(edev,
			"Can't support WoL options other than magic-packet\n");
		return -EINVAL;
	}

	wol_requested = !!(wol->wolopts & WAKE_MAGIC);
	if (wol_requested == edev->wol_enabled)
		return 0;

	/* Need to actually change configuration */
	if (!edev->dev_info.common.wol_support) {
		DP_INFO(edev, "Device doesn't support WoL\n");
		return -EINVAL;
	}

	rc = edev->ops->common->update_wol(edev->cdev, wol_requested);
	if (!rc)
		edev->wol_enabled = wol_requested;

	return rc;
}