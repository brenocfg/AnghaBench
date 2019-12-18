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
typedef  enum mlxsw_reg_ritr_counter_set_type { ____Placeholder_mlxsw_reg_ritr_counter_set_type } mlxsw_reg_ritr_counter_set_type ;

/* Variables and functions */
 int MLXSW_REG_RITR_COUNTER_SET_TYPE_BASIC ; 
 int MLXSW_REG_RITR_COUNTER_SET_TYPE_NO_COUNT ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_egress_counter_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_egress_counter_set_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_ingress_counter_index_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_ritr_counter_pack(char *payload, u32 index,
					       bool enable, bool egress)
{
	enum mlxsw_reg_ritr_counter_set_type set_type;

	if (enable)
		set_type = MLXSW_REG_RITR_COUNTER_SET_TYPE_BASIC;
	else
		set_type = MLXSW_REG_RITR_COUNTER_SET_TYPE_NO_COUNT;
	mlxsw_reg_ritr_egress_counter_set_type_set(payload, set_type);

	if (egress)
		mlxsw_reg_ritr_egress_counter_index_set(payload, index);
	else
		mlxsw_reg_ritr_ingress_counter_index_set(payload, index);
}