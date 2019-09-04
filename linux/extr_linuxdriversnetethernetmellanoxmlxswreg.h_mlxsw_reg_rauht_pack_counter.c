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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_counter_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_counter_set_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_rauht_pack_counter(char *payload,
						u64 counter_index)
{
	mlxsw_reg_rauht_counter_index_set(payload, counter_index);
	mlxsw_reg_rauht_counter_set_type_set(payload,
					     MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
}