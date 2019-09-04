#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int real; } ;
struct TYPE_23__ {int /*<<< orphan*/  full; TYPE_1__ partial; } ;
typedef  TYPE_2__ fInt ;

/* Variables and functions */
 int ConvertBackToInteger (TYPE_2__) ; 
 TYPE_2__ ConvertToFraction (int) ; 
 scalar_t__ Equal (TYPE_2__,TYPE_2__) ; 
 scalar_t__ GreaterThan (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ fDivide (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ fGetSquare (TYPE_2__) ; 
 TYPE_2__ fMultiply (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ fSubtract (TYPE_2__,TYPE_2__) ; 
 scalar_t__ uAbs (int) ; 

__attribute__((used)) static fInt fSqrt(fInt num)
{
	fInt F_divide_Fprime, Fprime;
	fInt test;
	fInt twoShifted;
	int seed, counter, error;
	fInt x_new, x_old, C, y;

	fInt fZERO = ConvertToFraction(0);

	/* (0 > num) is the same as (num < 0), i.e., num is negative */

	if (GreaterThan(fZERO, num) || Equal(fZERO, num))
		return fZERO;

	C = num;

	if (num.partial.real > 3000)
		seed = 60;
	else if (num.partial.real > 1000)
		seed = 30;
	else if (num.partial.real > 100)
		seed = 10;
	else
		seed = 2;

	counter = 0;

	if (Equal(num, fZERO)) /*Square Root of Zero is zero */
		return fZERO;

	twoShifted = ConvertToFraction(2);
	x_new = ConvertToFraction(seed);

	do {
		counter++;

		x_old.full = x_new.full;

		test = fGetSquare(x_old); /*1.75*1.75 is reverting back to 1 when shifted down */
		y = fSubtract(test, C); /*y = f(x) = x^2 - C; */

		Fprime = fMultiply(twoShifted, x_old);
		F_divide_Fprime = fDivide(y, Fprime);

		x_new = fSubtract(x_old, F_divide_Fprime);

		error = ConvertBackToInteger(x_new) - ConvertBackToInteger(x_old);

		if (counter > 20) /*20 is already way too many iterations. If we dont have an answer by then, we never will*/
			return x_new;

	} while (uAbs(error) > 0);

	return (x_new);
}