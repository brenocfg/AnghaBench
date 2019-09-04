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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  m_can_netdev_ops ; 
 int register_candev (struct net_device*) ; 

__attribute__((used)) static int register_m_can_dev(struct net_device *dev)
{
	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &m_can_netdev_ops;

	return register_candev(dev);
}