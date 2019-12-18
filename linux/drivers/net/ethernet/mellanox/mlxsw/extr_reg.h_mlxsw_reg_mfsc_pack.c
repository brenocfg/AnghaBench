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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mfsc ; 
 int /*<<< orphan*/  mlxsw_reg_mfsc_pwm_duty_cycle_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mfsc_pwm_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mfsc_pack(char *payload, u8 pwm,
				       u8 pwm_duty_cycle)
{
	MLXSW_REG_ZERO(mfsc, payload);
	mlxsw_reg_mfsc_pwm_set(payload, pwm);
	mlxsw_reg_mfsc_pwm_duty_cycle_set(payload, pwm_duty_cycle);
}