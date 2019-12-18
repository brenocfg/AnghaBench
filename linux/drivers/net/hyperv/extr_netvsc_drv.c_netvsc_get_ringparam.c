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
struct netvsc_device {int dummy; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netvsc_get_ringparam (struct netvsc_device*,struct ethtool_ringparam*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netvsc_get_ringparam(struct net_device *ndev,
				 struct ethtool_ringparam *ring)
{
	struct net_device_context *ndevctx = netdev_priv(ndev);
	struct netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);

	if (!nvdev)
		return;

	__netvsc_get_ringparam(nvdev, ring);
}