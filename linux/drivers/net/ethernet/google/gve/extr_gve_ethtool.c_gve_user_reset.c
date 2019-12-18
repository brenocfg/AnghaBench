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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct gve_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ ETH_RESET_ALL ; 
 int gve_reset (struct gve_priv*,int) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gve_user_reset(struct net_device *netdev, u32 *flags)
{
	struct gve_priv *priv = netdev_priv(netdev);

	if (*flags == ETH_RESET_ALL) {
		*flags = 0;
		return gve_reset(priv, true);
	}

	return -EOPNOTSUPP;
}