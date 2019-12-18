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
struct team_port {int dummy; } ;
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;

/* Variables and functions */
 scalar_t__ netif_is_team_port (struct net_device const*) ; 
 struct team_port* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct team_port *team_port_get_rtnl(const struct net_device *dev)
{
	struct team_port *port = rtnl_dereference(dev->rx_handler_data);

	return netif_is_team_port(dev) ? port : NULL;
}