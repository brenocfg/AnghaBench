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
struct net_device {int flags; int mtu; } ;
struct gfar_private {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFAR_RESETTING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  startup_gfar (struct net_device*) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfar_change_mtu(struct net_device *dev, int new_mtu)
{
	struct gfar_private *priv = netdev_priv(dev);

	while (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	if (dev->flags & IFF_UP)
		stop_gfar(dev);

	dev->mtu = new_mtu;

	if (dev->flags & IFF_UP)
		startup_gfar(dev);

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	return 0;
}