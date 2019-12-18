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
struct mlxsw_sp_port {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int mlxsw_sp_port_hwtstamp_get (struct mlxsw_sp_port*,struct ifreq*) ; 
 int mlxsw_sp_port_hwtstamp_set (struct mlxsw_sp_port*,struct ifreq*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mlxsw_sp_port_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	switch (cmd) {
	case SIOCSHWTSTAMP:
		return mlxsw_sp_port_hwtstamp_set(mlxsw_sp_port, ifr);
	case SIOCGHWTSTAMP:
		return mlxsw_sp_port_hwtstamp_get(mlxsw_sp_port, ifr);
	default:
		return -EOPNOTSUPP;
	}
}