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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_PAUSE_DELAY ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_pfc_delay_get (struct mlxsw_sp const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 mlxsw_sp_pg_buf_delay_get(const struct mlxsw_sp *mlxsw_sp, int mtu,
				     u16 delay, bool pfc, bool pause)
{
	if (pfc)
		return mlxsw_sp_pfc_delay_get(mlxsw_sp, mtu, delay);
	else if (pause)
		return mlxsw_sp_bytes_cells(mlxsw_sp, MLXSW_SP_PAUSE_DELAY);
	else
		return 0;
}