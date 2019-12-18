#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_6__ {scalar_t__ real; scalar_t__ decimal; } ;
struct TYPE_7__ {scalar_t__ full; TYPE_1__ partial; } ;
typedef  TYPE_2__ fInt ;

/* Variables and functions */

__attribute__((used)) static fInt fMultiply (fInt X, fInt Y) /* Uses 64-bit integers (int64_t) */
{
	fInt Product;
	int64_t tempProduct;
	bool X_LessThanOne, Y_LessThanOne;

	X_LessThanOne = (X.partial.real == 0 && X.partial.decimal != 0 && X.full >= 0);
	Y_LessThanOne = (Y.partial.real == 0 && Y.partial.decimal != 0 && Y.full >= 0);

	/*The following is for a very specific common case: Non-zero number with ONLY fractional portion*/
	/* TEMPORARILY DISABLED - CAN BE USED TO IMPROVE PRECISION

	if (X_LessThanOne && Y_LessThanOne) {
		Product.full = X.full * Y.full;
		return Product
	}*/

	tempProduct = ((int64_t)X.full) * ((int64_t)Y.full); /*Q(16,16)*Q(16,16) = Q(32, 32) - Might become a negative number! */
	tempProduct = tempProduct >> 16; /*Remove lagging 16 bits - Will lose some precision from decimal; */
	Product.full = (int)tempProduct; /*The int64_t will lose the leading 16 bits that were part of the integer portion */

	return Product;
}