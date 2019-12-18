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
typedef  enum mlxsw_reg_rauhtd_type { ____Placeholder_mlxsw_reg_rauhtd_type } mlxsw_reg_rauhtd_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RAUHTD_FILTER_A ; 
 int /*<<< orphan*/  MLXSW_REG_RAUHTD_OP_DUMP_AND_CLEAR ; 
 int /*<<< orphan*/  MLXSW_REG_RAUHTD_REC_MAX_NUM ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_entry_a_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_filter_fields_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_num_rec_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_op_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_type_set (char*,int) ; 
 int /*<<< orphan*/  rauhtd ; 

__attribute__((used)) static inline void mlxsw_reg_rauhtd_pack(char *payload,
					 enum mlxsw_reg_rauhtd_type type)
{
	MLXSW_REG_ZERO(rauhtd, payload);
	mlxsw_reg_rauhtd_filter_fields_set(payload, MLXSW_REG_RAUHTD_FILTER_A);
	mlxsw_reg_rauhtd_op_set(payload, MLXSW_REG_RAUHTD_OP_DUMP_AND_CLEAR);
	mlxsw_reg_rauhtd_num_rec_set(payload, MLXSW_REG_RAUHTD_REC_MAX_NUM);
	mlxsw_reg_rauhtd_entry_a_set(payload, 1);
	mlxsw_reg_rauhtd_type_set(payload, type);
}