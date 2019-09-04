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
struct isl29501_private {int dummy; } ;
typedef  enum isl29501_register_name { ____Placeholder_isl29501_register_name } isl29501_register_name ;
typedef  enum isl29501_correction_coeff { ____Placeholder_isl29501_correction_coeff } isl29501_correction_coeff ;

/* Variables and functions */
#define  COEFF_LIGHT_A 131 
#define  COEFF_LIGHT_B 130 
#define  COEFF_TEMP_A 129 
#define  COEFF_TEMP_B 128 
 int EINVAL ; 
 int REG_CALIB_PHASE_LIGHT_A ; 
 int REG_CALIB_PHASE_LIGHT_B ; 
 int REG_CALIB_PHASE_TEMP_A ; 
 int REG_CALIB_PHASE_TEMP_B ; 
 int isl29501_register_write (struct isl29501_private*,int,int) ; 

__attribute__((used)) static int isl29501_write_coeff(struct isl29501_private *isl29501,
				enum isl29501_correction_coeff coeff,
				int val)
{
	enum isl29501_register_name reg;

	switch (coeff) {
	case COEFF_TEMP_A:
		reg = REG_CALIB_PHASE_TEMP_A;
		break;
	case COEFF_TEMP_B:
		reg = REG_CALIB_PHASE_TEMP_B;
		break;
	case COEFF_LIGHT_A:
		reg = REG_CALIB_PHASE_LIGHT_A;
		break;
	case COEFF_LIGHT_B:
		reg = REG_CALIB_PHASE_LIGHT_B;
		break;
	default:
		return -EINVAL;
	}

	return isl29501_register_write(isl29501, reg, val);
}