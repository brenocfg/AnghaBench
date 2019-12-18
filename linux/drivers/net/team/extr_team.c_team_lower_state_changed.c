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
struct team_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  linkup; } ;
struct netdev_lag_lower_state_info {int /*<<< orphan*/  tx_enabled; int /*<<< orphan*/  link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_lower_state_changed (int /*<<< orphan*/ ,struct netdev_lag_lower_state_info*) ; 
 int /*<<< orphan*/  team_port_enabled (struct team_port*) ; 

__attribute__((used)) static void team_lower_state_changed(struct team_port *port)
{
	struct netdev_lag_lower_state_info info;

	info.link_up = port->linkup;
	info.tx_enabled = team_port_enabled(port);
	netdev_lower_state_changed(port->dev, &info);
}