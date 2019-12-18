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
typedef  int u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int MLXSW_SP_CELL_FACTOR ; 
 int mlxsw_sp_bytes_cells (struct mlxsw_sp const*,int) ; 

__attribute__((used)) static u16 mlxsw_sp_pfc_delay_get(const struct mlxsw_sp *mlxsw_sp, int mtu,
				  u16 delay)
{
	delay = mlxsw_sp_bytes_cells(mlxsw_sp, DIV_ROUND_UP(delay,
							    BITS_PER_BYTE));
	return MLXSW_SP_CELL_FACTOR * delay + mlxsw_sp_bytes_cells(mlxsw_sp,
								   mtu);
}