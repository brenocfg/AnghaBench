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
typedef  enum mlxsw_reg_rauht_op { ____Placeholder_mlxsw_reg_rauht_op } mlxsw_reg_rauht_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_mac_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_rif_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rauht ; 

__attribute__((used)) static inline void mlxsw_reg_rauht_pack(char *payload,
					enum mlxsw_reg_rauht_op op, u16 rif,
					const char *mac)
{
	MLXSW_REG_ZERO(rauht, payload);
	mlxsw_reg_rauht_op_set(payload, op);
	mlxsw_reg_rauht_rif_set(payload, rif);
	mlxsw_reg_rauht_mac_memcpy_to(payload, mac);
}