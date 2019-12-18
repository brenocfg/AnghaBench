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
struct udp_tunnel_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cfg_vxlan_port (struct net_device*,struct udp_tunnel_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_work_add_vxlan_port ; 

__attribute__((used)) static void be_add_vxlan_port(struct net_device *netdev,
			      struct udp_tunnel_info *ti)
{
	be_cfg_vxlan_port(netdev, ti, be_work_add_vxlan_port);
}