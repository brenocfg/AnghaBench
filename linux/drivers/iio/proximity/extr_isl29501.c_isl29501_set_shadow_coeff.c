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
struct isl29501_private {unsigned int* shadow_coeffs; } ;
typedef  enum isl29501_register_name { ____Placeholder_isl29501_register_name } isl29501_register_name ;
typedef  enum isl29501_correction_coeff { ____Placeholder_isl29501_correction_coeff } isl29501_correction_coeff ;

/* Variables and functions */
 int COEFF_LIGHT_A ; 
 int COEFF_LIGHT_B ; 
 int COEFF_TEMP_A ; 
 int COEFF_TEMP_B ; 
 int EINVAL ; 
#define  REG_CALIB_PHASE_LIGHT_A 131 
#define  REG_CALIB_PHASE_LIGHT_B 130 
#define  REG_CALIB_PHASE_TEMP_A 129 
#define  REG_CALIB_PHASE_TEMP_B 128 

__attribute__((used)) static int isl29501_set_shadow_coeff(struct isl29501_private *isl29501,
				     enum isl29501_register_name reg,
				     unsigned int val)
{
	enum isl29501_correction_coeff coeff;

	switch (reg) {
	case REG_CALIB_PHASE_TEMP_A:
		coeff = COEFF_TEMP_A;
		break;
	case REG_CALIB_PHASE_TEMP_B:
		coeff = COEFF_TEMP_B;
		break;
	case REG_CALIB_PHASE_LIGHT_A:
		coeff = COEFF_LIGHT_A;
		break;
	case REG_CALIB_PHASE_LIGHT_B:
		coeff = COEFF_LIGHT_B;
		break;
	default:
		return -EINVAL;
	}
	isl29501->shadow_coeffs[coeff] = val;

	return 0;
}