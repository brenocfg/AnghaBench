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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxrate; } ;
struct mlxsw_sp_port {TYPE_1__ dcb; } ;
struct ieee_maxrate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ieee_maxrate*,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_dcbnl_ieee_getmaxrate(struct net_device *dev,
					  struct ieee_maxrate *maxrate)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	memcpy(maxrate, mlxsw_sp_port->dcb.maxrate, sizeof(*maxrate));

	return 0;
}