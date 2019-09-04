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
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 130 
#define  TC_SETUP_QDISC_PRIO 129 
#define  TC_SETUP_QDISC_RED 128 
 int mlxsw_sp_setup_tc_block (struct mlxsw_sp_port*,void*) ; 
 int mlxsw_sp_setup_tc_prio (struct mlxsw_sp_port*,void*) ; 
 int mlxsw_sp_setup_tc_red (struct mlxsw_sp_port*,void*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc(struct net_device *dev, enum tc_setup_type type,
			     void *type_data)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return mlxsw_sp_setup_tc_block(mlxsw_sp_port, type_data);
	case TC_SETUP_QDISC_RED:
		return mlxsw_sp_setup_tc_red(mlxsw_sp_port, type_data);
	case TC_SETUP_QDISC_PRIO:
		return mlxsw_sp_setup_tc_prio(mlxsw_sp_port, type_data);
	default:
		return -EOPNOTSUPP;
	}
}