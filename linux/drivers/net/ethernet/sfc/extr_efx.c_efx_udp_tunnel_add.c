#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct udp_tunnel_info {int /*<<< orphan*/  port; int /*<<< orphan*/  type; } ;
struct net_device {int dummy; } ;
struct efx_udp_tunnel {int /*<<< orphan*/  port; scalar_t__ type; } ;
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* udp_tnl_add_port ) (struct efx_nic*,struct efx_udp_tunnel) ;} ;

/* Variables and functions */
 int efx_udp_tunnel_type_map (int /*<<< orphan*/ ) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,struct efx_udp_tunnel) ; 

__attribute__((used)) static void efx_udp_tunnel_add(struct net_device *dev, struct udp_tunnel_info *ti)
{
	struct efx_nic *efx = netdev_priv(dev);
	struct efx_udp_tunnel tnl;
	int efx_tunnel_type;

	efx_tunnel_type = efx_udp_tunnel_type_map(ti->type);
	if (efx_tunnel_type < 0)
		return;

	tnl.type = (u16)efx_tunnel_type;
	tnl.port = ti->port;

	if (efx->type->udp_tnl_add_port)
		(void)efx->type->udp_tnl_add_port(efx, tnl);
}