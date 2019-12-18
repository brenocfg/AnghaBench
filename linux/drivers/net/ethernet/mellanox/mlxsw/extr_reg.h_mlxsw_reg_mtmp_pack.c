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
 int /*<<< orphan*/  MLXSW_REG_MTMP_THRESH_HI ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_mte_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_mtr_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_sensor_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_temperature_threshold_hi_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmp ; 

__attribute__((used)) static inline void mlxsw_reg_mtmp_pack(char *payload, u16 sensor_index,
				       bool max_temp_enable,
				       bool max_temp_reset)
{
	MLXSW_REG_ZERO(mtmp, payload);
	mlxsw_reg_mtmp_sensor_index_set(payload, sensor_index);
	mlxsw_reg_mtmp_mte_set(payload, max_temp_enable);
	mlxsw_reg_mtmp_mtr_set(payload, max_temp_reset);
	mlxsw_reg_mtmp_temperature_threshold_hi_set(payload,
						    MLXSW_REG_MTMP_THRESH_HI);
}