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
 int /*<<< orphan*/  MLXSW_REG_MTPPS_PIN_MODE_VIRTUAL_PIN ; 
 int /*<<< orphan*/  MLXSW_REG_MTPPS_PIN_SP_VIRTUAL_PIN ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpps_enable_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpps_pin_mode_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpps_pin_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpps_time_stamp_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtpps ; 

__attribute__((used)) static inline void
mlxsw_reg_mtpps_vpin_pack(char *payload, u64 time_stamp)
{
	MLXSW_REG_ZERO(mtpps, payload);
	mlxsw_reg_mtpps_pin_set(payload, MLXSW_REG_MTPPS_PIN_SP_VIRTUAL_PIN);
	mlxsw_reg_mtpps_pin_mode_set(payload,
				     MLXSW_REG_MTPPS_PIN_MODE_VIRTUAL_PIN);
	mlxsw_reg_mtpps_enable_set(payload, true);
	mlxsw_reg_mtpps_time_stamp_set(payload, time_stamp);
}