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
struct net_device {TYPE_1__* ethtool_ops; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  drvinfo ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_drvinfo ) (struct net_device*,struct ethtool_drvinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_drvinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct ethtool_drvinfo*) ; 

__attribute__((used)) static bool is_bnxt_re_dev(struct net_device *netdev)
{
	struct ethtool_drvinfo drvinfo;

	if (netdev->ethtool_ops && netdev->ethtool_ops->get_drvinfo) {
		memset(&drvinfo, 0, sizeof(drvinfo));
		netdev->ethtool_ops->get_drvinfo(netdev, &drvinfo);

		if (strcmp(drvinfo.driver, "bnxt_en"))
			return false;
		return true;
	}
	return false;
}