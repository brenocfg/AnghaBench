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
struct ql_adapter {int wol; int /*<<< orphan*/  ndev; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {unsigned short subsystem_device; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned short QLGE_MEZZ_SSYS_ID_068 ; 
 unsigned short QLGE_MEZZ_SSYS_ID_180 ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  drv ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ql_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	unsigned short ssys_dev = qdev->pdev->subsystem_device;

	/* WOL is only supported for mezz card. */
	if (ssys_dev != QLGE_MEZZ_SSYS_ID_068 &&
			ssys_dev != QLGE_MEZZ_SSYS_ID_180) {
		netif_info(qdev, drv, qdev->ndev,
				"WOL is only supported for mezz card\n");
		return -EOPNOTSUPP;
	}
	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;
	qdev->wol = wol->wolopts;

	netif_info(qdev, drv, qdev->ndev, "Set wol option 0x%x\n", qdev->wol);
	return 0;
}