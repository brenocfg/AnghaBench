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
struct udp_tunnel_info {scalar_t__ type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCTNET_CMD_VXLAN_PORT_CONFIG ; 
 int /*<<< orphan*/  OCTNET_CMD_VXLAN_PORT_DEL ; 
 scalar_t__ UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  liquidio_vxlan_port_command (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void liquidio_del_vxlan_port(struct net_device *netdev,
				    struct udp_tunnel_info *ti)
{
	if (ti->type != UDP_TUNNEL_TYPE_VXLAN)
		return;

	liquidio_vxlan_port_command(netdev,
				    OCTNET_CMD_VXLAN_PORT_CONFIG,
				    htons(ti->port),
				    OCTNET_CMD_VXLAN_PORT_DEL);
}