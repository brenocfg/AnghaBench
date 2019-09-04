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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdat_age_time_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdat_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfdat ; 

__attribute__((used)) static inline void mlxsw_reg_sfdat_pack(char *payload, u32 age_time)
{
	MLXSW_REG_ZERO(sfdat, payload);
	mlxsw_reg_sfdat_swid_set(payload, 0);
	mlxsw_reg_sfdat_age_time_set(payload, age_time);
}