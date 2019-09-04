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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct si1133_coeff {scalar_t__ info; int mag; } ;
typedef  int s8 ;

/* Variables and functions */
 int SI1133_LUX_OUTPUT_FRACTION ; 
 int abs (int) ; 
 scalar_t__ si1133_calculate_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,struct si1133_coeff const*) ; 
 scalar_t__ si1133_get_x_order (scalar_t__) ; 
 scalar_t__ si1133_get_y_order (scalar_t__) ; 

__attribute__((used)) static int si1133_calc_polynomial(u32 x, u32 y, u8 input_fraction, u8 num_coeff,
				  const struct si1133_coeff *coeffs)
{
	u8 x_order, y_order;
	u8 counter;
	s8 sign;
	int output = 0;

	for (counter = 0; counter < num_coeff; counter++) {
		if (coeffs->info < 0)
			sign = -1;
		else
			sign = 1;

		x_order = si1133_get_x_order(coeffs->info);
		y_order = si1133_get_y_order(coeffs->info);

		if ((x_order == 0) && (y_order == 0))
			output +=
			       sign * coeffs->mag << SI1133_LUX_OUTPUT_FRACTION;
		else
			output += si1133_calculate_output(x, y, x_order,
							  y_order,
							  input_fraction, sign,
							  coeffs);
		coeffs++;
	}

	return abs(output);
}