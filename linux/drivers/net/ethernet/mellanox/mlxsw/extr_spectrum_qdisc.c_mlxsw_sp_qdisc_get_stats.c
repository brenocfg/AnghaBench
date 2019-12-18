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
struct tc_qopt_offload_stats {int dummy; } ;
struct mlxsw_sp_qdisc {TYPE_1__* ops; } ;
struct mlxsw_sp_port {int dummy; } ;
struct TYPE_2__ {int (* get_stats ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,struct tc_qopt_offload_stats*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,struct tc_qopt_offload_stats*) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_get_stats(struct mlxsw_sp_port *mlxsw_sp_port,
			 struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			 struct tc_qopt_offload_stats *stats_ptr)
{
	if (mlxsw_sp_qdisc && mlxsw_sp_qdisc->ops &&
	    mlxsw_sp_qdisc->ops->get_stats)
		return mlxsw_sp_qdisc->ops->get_stats(mlxsw_sp_port,
						      mlxsw_sp_qdisc,
						      stats_ptr);

	return -EOPNOTSUPP;
}