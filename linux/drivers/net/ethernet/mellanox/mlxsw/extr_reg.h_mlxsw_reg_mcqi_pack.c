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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_MCQI_CAP_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MCQI_INFO_TYPE_CAPABILITIES ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcqi ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_component_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_data_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_info_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_offset_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mcqi_pack(char *payload, u16 component_index)
{
	MLXSW_REG_ZERO(mcqi, payload);
	mlxsw_reg_mcqi_component_index_set(payload, component_index);
	mlxsw_reg_mcqi_info_type_set(payload,
				     MLXSW_REG_MCQI_INFO_TYPE_CAPABILITIES);
	mlxsw_reg_mcqi_offset_set(payload, 0);
	mlxsw_reg_mcqi_data_size_set(payload, MLXSW_REG_MCQI_CAP_LEN);
}