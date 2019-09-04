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
struct TYPE_3__ {scalar_t__ wol_support; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct qede_dev {scalar_t__ wol_enabled; TYPE_2__ dev_info; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {void* wolopts; void* supported; } ;

/* Variables and functions */
 void* WAKE_MAGIC ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void qede_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct qede_dev *edev = netdev_priv(ndev);

	if (edev->dev_info.common.wol_support) {
		wol->supported = WAKE_MAGIC;
		wol->wolopts = edev->wol_enabled ? WAKE_MAGIC : 0;
	}
}