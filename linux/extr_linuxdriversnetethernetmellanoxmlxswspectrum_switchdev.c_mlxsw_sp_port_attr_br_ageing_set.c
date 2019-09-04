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
typedef  scalar_t__ u32 ;
struct switchdev_trans {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ MLXSW_SP_MAX_AGEING_TIME ; 
 scalar_t__ MLXSW_SP_MIN_AGEING_TIME ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 
 int jiffies_to_msecs (unsigned long) ; 
 int mlxsw_sp_ageing_set (struct mlxsw_sp*,scalar_t__) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int mlxsw_sp_port_attr_br_ageing_set(struct mlxsw_sp_port *mlxsw_sp_port,
					    struct switchdev_trans *trans,
					    unsigned long ageing_clock_t)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	unsigned long ageing_jiffies = clock_t_to_jiffies(ageing_clock_t);
	u32 ageing_time = jiffies_to_msecs(ageing_jiffies) / 1000;

	if (switchdev_trans_ph_prepare(trans)) {
		if (ageing_time < MLXSW_SP_MIN_AGEING_TIME ||
		    ageing_time > MLXSW_SP_MAX_AGEING_TIME)
			return -ERANGE;
		else
			return 0;
	}

	return mlxsw_sp_ageing_set(mlxsw_sp, ageing_time);
}