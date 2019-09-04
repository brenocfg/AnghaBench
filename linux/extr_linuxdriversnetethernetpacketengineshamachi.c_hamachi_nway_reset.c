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
struct hamachi_private {int /*<<< orphan*/  mii_if; } ;

/* Variables and functions */
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct hamachi_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hamachi_nway_reset(struct net_device *dev)
{
	struct hamachi_private *np = netdev_priv(dev);
	return mii_nway_restart(&np->mii_if);
}