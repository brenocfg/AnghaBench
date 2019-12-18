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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct si1133_coeff {int /*<<< orphan*/  mag; scalar_t__ info; } ;
typedef  int s8 ;

/* Variables and functions */
 int si1133_calculate_polynomial_inner (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si1133_calculate_output(u32 x, u32 y, u8 x_order, u8 y_order,
				   u8 input_fraction, s8 sign,
				   const struct si1133_coeff *coeffs)
{
	s8 shift;
	int x1 = 1;
	int x2 = 1;
	int y1 = 1;
	int y2 = 1;

	shift = ((u16)coeffs->info & 0xFF00) >> 8;
	shift ^= 0xFF;
	shift += 1;
	shift = -shift;

	if (x_order > 0) {
		x1 = si1133_calculate_polynomial_inner(x, input_fraction,
						       coeffs->mag, shift);
		if (x_order > 1)
			x2 = x1;
	}

	if (y_order > 0) {
		y1 = si1133_calculate_polynomial_inner(y, input_fraction,
						       coeffs->mag, shift);
		if (y_order > 1)
			y2 = y1;
	}

	return sign * x1 * x2 * y1 * y2;
}