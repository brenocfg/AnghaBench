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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_slcor_col { ____Placeholder_mlxsw_reg_slcor_col } mlxsw_reg_slcor_col ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_slcor_col_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_slcor_lag_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_slcor_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slcor ; 

__attribute__((used)) static inline void mlxsw_reg_slcor_pack(char *payload,
					u8 local_port, u16 lag_id,
					enum mlxsw_reg_slcor_col col)
{
	MLXSW_REG_ZERO(slcor, payload);
	mlxsw_reg_slcor_col_set(payload, col);
	mlxsw_reg_slcor_local_port_set(payload, local_port);
	mlxsw_reg_slcor_lag_id_set(payload, lag_id);
}