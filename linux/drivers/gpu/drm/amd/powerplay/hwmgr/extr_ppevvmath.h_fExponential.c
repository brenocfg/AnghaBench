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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  fInt ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToFraction (int) ; 
 int /*<<< orphan*/  Divide (int,int) ; 
 int /*<<< orphan*/  GetScaledFraction (int const,int) ; 
 scalar_t__ GreaterThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fDivide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fNegate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fInt fExponential(fInt exponent)        /*Can be used to calculate e^exponent*/
{
	uint32_t i;
	bool bNegated = false;

	fInt fPositiveOne = ConvertToFraction(1);
	fInt fZERO = ConvertToFraction(0);

	fInt lower_bound = Divide(78, 10000);
	fInt solution = fPositiveOne; /*Starting off with baseline of 1 */
	fInt error_term;

	static const uint32_t k_array[11] = {55452, 27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78};
	static const uint32_t expk_array[11] = {2560000, 160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078};

	if (GreaterThan(fZERO, exponent)) {
		exponent = fNegate(exponent);
		bNegated = true;
	}

	while (GreaterThan(exponent, lower_bound)) {
		for (i = 0; i < 11; i++) {
			if (GreaterThan(exponent, GetScaledFraction(k_array[i], 10000))) {
				exponent = fSubtract(exponent, GetScaledFraction(k_array[i], 10000));
				solution = fMultiply(solution, GetScaledFraction(expk_array[i], 10000));
			}
		}
	}

	error_term = fAdd(fPositiveOne, exponent);

	solution = fMultiply(solution, error_term);

	if (bNegated)
		solution = fDivide(fPositiveOne, solution);

	return solution;
}