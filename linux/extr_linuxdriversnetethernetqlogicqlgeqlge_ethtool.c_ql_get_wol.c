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
struct ql_adapter {int /*<<< orphan*/  wol; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct TYPE_2__ {unsigned short subsystem_device; } ;

/* Variables and functions */
 unsigned short QLGE_MEZZ_SSYS_ID_068 ; 
 unsigned short QLGE_MEZZ_SSYS_ID_180 ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ql_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	unsigned short ssys_dev = qdev->pdev->subsystem_device;

	/* WOL is only supported for mezz card. */
	if (ssys_dev == QLGE_MEZZ_SSYS_ID_068 ||
			ssys_dev == QLGE_MEZZ_SSYS_ID_180) {
		wol->supported = WAKE_MAGIC;
		wol->wolopts = qdev->wol;
	}
}