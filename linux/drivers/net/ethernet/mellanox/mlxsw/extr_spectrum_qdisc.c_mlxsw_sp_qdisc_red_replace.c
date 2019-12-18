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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tc_red_qopt_offload_params {int probability; int /*<<< orphan*/  is_ecn; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct mlxsw_sp_qdisc {int /*<<< orphan*/  tclass_num; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_tclass_congestion_enable (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_red_replace(struct mlxsw_sp_port *mlxsw_sp_port,
			   struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			   void *params)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct tc_red_qopt_offload_params *p = params;
	u8 tclass_num = mlxsw_sp_qdisc->tclass_num;
	u32 min, max;
	u64 prob;

	/* calculate probability in percentage */
	prob = p->probability;
	prob *= 100;
	prob = DIV_ROUND_UP(prob, 1 << 16);
	prob = DIV_ROUND_UP(prob, 1 << 16);
	min = mlxsw_sp_bytes_cells(mlxsw_sp, p->min);
	max = mlxsw_sp_bytes_cells(mlxsw_sp, p->max);
	return mlxsw_sp_tclass_congestion_enable(mlxsw_sp_port, tclass_num, min,
						 max, prob, p->is_ecn);
}