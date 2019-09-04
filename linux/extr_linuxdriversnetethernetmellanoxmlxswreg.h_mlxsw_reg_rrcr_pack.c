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
typedef  enum mlxsw_reg_rtar_key_type { ____Placeholder_mlxsw_reg_rtar_key_type } mlxsw_reg_rtar_key_type ;
typedef  enum mlxsw_reg_rrcr_op { ____Placeholder_mlxsw_reg_rrcr_op } mlxsw_reg_rrcr_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_dest_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_table_id_set (char*,int) ; 
 int /*<<< orphan*/  rrcr ; 

__attribute__((used)) static inline void mlxsw_reg_rrcr_pack(char *payload, enum mlxsw_reg_rrcr_op op,
				       u16 offset, u16 size,
				       enum mlxsw_reg_rtar_key_type table_id,
				       u16 dest_offset)
{
	MLXSW_REG_ZERO(rrcr, payload);
	mlxsw_reg_rrcr_op_set(payload, op);
	mlxsw_reg_rrcr_offset_set(payload, offset);
	mlxsw_reg_rrcr_size_set(payload, size);
	mlxsw_reg_rrcr_table_id_set(payload, table_id);
	mlxsw_reg_rrcr_dest_offset_set(payload, dest_offset);
}