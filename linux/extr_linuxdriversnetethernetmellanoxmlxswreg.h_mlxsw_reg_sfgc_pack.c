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
typedef  enum mlxsw_reg_sfgc_type { ____Placeholder_mlxsw_reg_sfgc_type } mlxsw_reg_sfgc_type ;
typedef  enum mlxsw_reg_sfgc_bridge_type { ____Placeholder_mlxsw_reg_sfgc_bridge_type } mlxsw_reg_sfgc_bridge_type ;
typedef  enum mlxsw_flood_table_type { ____Placeholder_mlxsw_flood_table_type } mlxsw_flood_table_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_MID ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfgc_bridge_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfgc_flood_table_set (char*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfgc_mid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfgc_table_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfgc_type_set (char*,int) ; 
 int /*<<< orphan*/  sfgc ; 

__attribute__((used)) static inline void
mlxsw_reg_sfgc_pack(char *payload, enum mlxsw_reg_sfgc_type type,
		    enum mlxsw_reg_sfgc_bridge_type bridge_type,
		    enum mlxsw_flood_table_type table_type,
		    unsigned int flood_table)
{
	MLXSW_REG_ZERO(sfgc, payload);
	mlxsw_reg_sfgc_type_set(payload, type);
	mlxsw_reg_sfgc_bridge_type_set(payload, bridge_type);
	mlxsw_reg_sfgc_table_type_set(payload, table_type);
	mlxsw_reg_sfgc_flood_table_set(payload, flood_table);
	mlxsw_reg_sfgc_mid_set(payload, MLXSW_PORT_MID);
}