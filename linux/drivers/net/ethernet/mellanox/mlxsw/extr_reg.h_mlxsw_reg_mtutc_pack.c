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
typedef  enum mlxsw_reg_mtutc_operation { ____Placeholder_mlxsw_reg_mtutc_operation } mlxsw_reg_mtutc_operation ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtutc_freq_adjustment_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mtutc_operation_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtutc_utc_sec_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtutc ; 

__attribute__((used)) static inline void
mlxsw_reg_mtutc_pack(char *payload, enum mlxsw_reg_mtutc_operation oper,
		     u32 freq_adj, u32 utc_sec)
{
	MLXSW_REG_ZERO(mtutc, payload);
	mlxsw_reg_mtutc_operation_set(payload, oper);
	mlxsw_reg_mtutc_freq_adjustment_set(payload, freq_adj);
	mlxsw_reg_mtutc_utc_sec_set(payload, utc_sec);
}