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

/* Variables and functions */

__attribute__((used)) static void
isdn_net_reset(struct net_device *dev)
{
#ifdef CONFIG_ISDN_X25
	struct concap_device_ops *dops =
		((isdn_net_local *)netdev_priv(dev))->dops;
	struct concap_proto *cprot =
		((isdn_net_local *)netdev_priv(dev))->netdev->cprot;
#endif
#ifdef CONFIG_ISDN_X25
	if (cprot && cprot->pops && dops)
		cprot->pops->restart(cprot, dev, dops);
#endif
}