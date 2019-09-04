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
struct ethtool_link_ksettings {int dummy; } ;
struct de_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __de_set_link_ksettings (struct de_private*,struct ethtool_link_ksettings const*) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int de_set_link_ksettings(struct net_device *dev,
				 const struct ethtool_link_ksettings *cmd)
{
	struct de_private *de = netdev_priv(dev);
	int rc;

	spin_lock_irq(&de->lock);
	rc = __de_set_link_ksettings(de, cmd);
	spin_unlock_irq(&de->lock);

	return rc;
}