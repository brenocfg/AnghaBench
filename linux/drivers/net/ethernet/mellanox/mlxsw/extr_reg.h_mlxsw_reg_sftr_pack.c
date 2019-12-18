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
typedef  enum mlxsw_flood_table_type { ____Placeholder_mlxsw_flood_table_type } mlxsw_flood_table_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_flood_table_set (char*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_index_set (char*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_port_mask_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_port_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_range_set (char*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_table_type_set (char*,int) ; 
 int /*<<< orphan*/  sftr ; 

__attribute__((used)) static inline void mlxsw_reg_sftr_pack(char *payload,
				       unsigned int flood_table,
				       unsigned int index,
				       enum mlxsw_flood_table_type table_type,
				       unsigned int range, u8 port, bool set)
{
	MLXSW_REG_ZERO(sftr, payload);
	mlxsw_reg_sftr_swid_set(payload, 0);
	mlxsw_reg_sftr_flood_table_set(payload, flood_table);
	mlxsw_reg_sftr_index_set(payload, index);
	mlxsw_reg_sftr_table_type_set(payload, table_type);
	mlxsw_reg_sftr_range_set(payload, range);
	mlxsw_reg_sftr_port_set(payload, port, set);
	mlxsw_reg_sftr_port_mask_set(payload, port, 1);
}