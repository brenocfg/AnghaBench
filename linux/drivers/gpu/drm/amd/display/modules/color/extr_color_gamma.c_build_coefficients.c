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
typedef  size_t uint32_t ;
struct gamma_coefficients {void** user_gamma; void** a3; void** a2; void** a1; void** a0; } ;
typedef  enum dc_transfer_func_predefined { ____Placeholder_dc_transfer_func_predefined } dc_transfer_func_predefined ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int TRANSFER_FUNCTION_BT709 ; 
 int TRANSFER_FUNCTION_GAMMA22 ; 
 int TRANSFER_FUNCTION_GAMMA24 ; 
 int TRANSFER_FUNCTION_GAMMA26 ; 
 int TRANSFER_FUNCTION_SRGB ; 
 void* dc_fixpt_from_fraction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gamma_numerator01 ; 
 int /*<<< orphan*/ * gamma_numerator02 ; 
 int /*<<< orphan*/ * gamma_numerator03 ; 
 int /*<<< orphan*/ * gamma_numerator04 ; 
 int /*<<< orphan*/ * gamma_numerator05 ; 

__attribute__((used)) static bool build_coefficients(struct gamma_coefficients *coefficients, enum dc_transfer_func_predefined type)
{

	uint32_t i = 0;
	uint32_t index = 0;
	bool ret = true;

	if (type == TRANSFER_FUNCTION_SRGB)
		index = 0;
	else if (type == TRANSFER_FUNCTION_BT709)
		index = 1;
	else if (type == TRANSFER_FUNCTION_GAMMA22)
		index = 2;
	else if (type == TRANSFER_FUNCTION_GAMMA24)
		index = 3;
	else if (type == TRANSFER_FUNCTION_GAMMA26)
		index = 4;
	else {
		ret = false;
		goto release;
	}

	do {
		coefficients->a0[i] = dc_fixpt_from_fraction(
			gamma_numerator01[index], 10000000);
		coefficients->a1[i] = dc_fixpt_from_fraction(
			gamma_numerator02[index], 1000);
		coefficients->a2[i] = dc_fixpt_from_fraction(
			gamma_numerator03[index], 1000);
		coefficients->a3[i] = dc_fixpt_from_fraction(
			gamma_numerator04[index], 1000);
		coefficients->user_gamma[i] = dc_fixpt_from_fraction(
			gamma_numerator05[index], 1000);

		++i;
	} while (i != ARRAY_SIZE(coefficients->a0));
release:
	return ret;
}