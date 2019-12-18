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
typedef  int /*<<< orphan*/  u64 ;
struct sky2_port {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sky2_phy_stats (struct sky2_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_stats ; 

__attribute__((used)) static void sky2_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 * data)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	sky2_phy_stats(sky2, data, ARRAY_SIZE(sky2_stats));
}