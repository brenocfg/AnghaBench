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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SLDR_OP_LAG_CREATE ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sldr_lag_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sldr_op_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldr ; 

__attribute__((used)) static inline void mlxsw_reg_sldr_lag_create_pack(char *payload, u8 lag_id)
{
	MLXSW_REG_ZERO(sldr, payload);
	mlxsw_reg_sldr_op_set(payload, MLXSW_REG_SLDR_OP_LAG_CREATE);
	mlxsw_reg_sldr_lag_id_set(payload, lag_id);
}