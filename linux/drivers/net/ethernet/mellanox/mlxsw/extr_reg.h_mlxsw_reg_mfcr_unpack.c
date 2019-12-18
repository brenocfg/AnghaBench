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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_mfcr_pwm_frequency { ____Placeholder_mlxsw_reg_mfcr_pwm_frequency } mlxsw_reg_mfcr_pwm_frequency ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mfcr_pwm_active_get (char*) ; 
 int mlxsw_reg_mfcr_pwm_frequency_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mfcr_tacho_active_get (char*) ; 

__attribute__((used)) static inline void
mlxsw_reg_mfcr_unpack(char *payload,
		      enum mlxsw_reg_mfcr_pwm_frequency *p_pwm_frequency,
		      u16 *p_tacho_active, u8 *p_pwm_active)
{
	*p_pwm_frequency = mlxsw_reg_mfcr_pwm_frequency_get(payload);
	*p_tacho_active = mlxsw_reg_mfcr_tacho_active_get(payload);
	*p_pwm_active = mlxsw_reg_mfcr_pwm_active_get(payload);
}