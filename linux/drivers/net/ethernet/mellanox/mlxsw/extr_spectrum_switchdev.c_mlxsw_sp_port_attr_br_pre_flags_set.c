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
struct switchdev_trans {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 unsigned long BR_FLOOD ; 
 unsigned long BR_LEARNING ; 
 unsigned long BR_MCAST_FLOOD ; 
 int EINVAL ; 

__attribute__((used)) static int mlxsw_sp_port_attr_br_pre_flags_set(struct mlxsw_sp_port
					       *mlxsw_sp_port,
					       struct switchdev_trans *trans,
					       unsigned long brport_flags)
{
	if (brport_flags & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD))
		return -EINVAL;

	return 0;
}