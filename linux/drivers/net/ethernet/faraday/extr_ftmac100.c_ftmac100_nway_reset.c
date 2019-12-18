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
struct ftmac100 {int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct ftmac100* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ftmac100_nway_reset(struct net_device *netdev)
{
	struct ftmac100 *priv = netdev_priv(netdev);
	return mii_nway_restart(&priv->mii);
}