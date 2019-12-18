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
struct mlxsw_sp {int dummy; } ;
struct mlxsw_reg_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp1_ptp_fifo_event_func (struct mlxsw_sp*,char*,int) ; 

__attribute__((used)) static void mlxsw_sp1_ptp_egr_fifo_event_func(const struct mlxsw_reg_info *reg,
					      char *mtpptr_pl, void *priv)
{
	struct mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp1_ptp_fifo_event_func(mlxsw_sp, mtpptr_pl, false);
}