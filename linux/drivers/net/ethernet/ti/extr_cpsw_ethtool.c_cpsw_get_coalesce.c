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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct cpsw_common {int /*<<< orphan*/  coal_intvl; } ;

/* Variables and functions */
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

int cpsw_get_coalesce(struct net_device *ndev, struct ethtool_coalesce *coal)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	coal->rx_coalesce_usecs = cpsw->coal_intvl;
	return 0;
}