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
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_xoff_refresh_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_xoff_timer_value_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbmc ; 

__attribute__((used)) static inline void mlxsw_reg_pbmc_pack(char *payload, u8 local_port,
				       u16 xoff_timer_value, u16 xoff_refresh)
{
	MLXSW_REG_ZERO(pbmc, payload);
	mlxsw_reg_pbmc_local_port_set(payload, local_port);
	mlxsw_reg_pbmc_xoff_timer_value_set(payload, xoff_timer_value);
	mlxsw_reg_pbmc_xoff_refresh_set(payload, xoff_refresh);
}