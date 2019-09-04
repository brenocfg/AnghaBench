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
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_ethtool_ops ; 

void hns_ethtool_set_ops(struct net_device *ndev)
{
	ndev->ethtool_ops = &hns_ethtool_ops;
}