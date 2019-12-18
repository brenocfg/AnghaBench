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
struct rocker_port {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct neighbour {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rocker_port* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int rocker_world_port_neigh_destroy (struct rocker_port*,struct neighbour*) ; 

__attribute__((used)) static void rocker_port_neigh_destroy(struct net_device *dev,
				      struct neighbour *n)
{
	struct rocker_port *rocker_port = netdev_priv(n->dev);
	int err;

	err = rocker_world_port_neigh_destroy(rocker_port, n);
	if (err)
		netdev_warn(rocker_port->dev, "failed to handle neigh destroy (err %d)\n",
			    err);
}