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
struct tc_prio_qopt_offload_params {scalar_t__ bands; } ;
struct mlxsw_sp_qdisc {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IEEE_8021QAZ_MAX_TCS ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_prio_check_params(struct mlxsw_sp_port *mlxsw_sp_port,
				 struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
				 void *params)
{
	struct tc_prio_qopt_offload_params *p = params;

	if (p->bands > IEEE_8021QAZ_MAX_TCS)
		return -EOPNOTSUPP;

	return 0;
}