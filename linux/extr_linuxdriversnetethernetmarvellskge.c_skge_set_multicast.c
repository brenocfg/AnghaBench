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
struct skge_port {int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  genesis_set_multicast (struct net_device*) ; 
 scalar_t__ is_genesis (int /*<<< orphan*/ ) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  yukon_set_multicast (struct net_device*) ; 

__attribute__((used)) static void skge_set_multicast(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);

	if (is_genesis(skge->hw))
		genesis_set_multicast(dev);
	else
		yukon_set_multicast(dev);

}