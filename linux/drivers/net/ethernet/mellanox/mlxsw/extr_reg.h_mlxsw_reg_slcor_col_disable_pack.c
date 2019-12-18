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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_ENABLED ; 
 int /*<<< orphan*/  mlxsw_reg_slcor_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_slcor_col_disable_pack(char *payload,
						    u8 local_port, u16 lag_id)
{
	mlxsw_reg_slcor_pack(payload, local_port, lag_id,
			     MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_ENABLED);
}