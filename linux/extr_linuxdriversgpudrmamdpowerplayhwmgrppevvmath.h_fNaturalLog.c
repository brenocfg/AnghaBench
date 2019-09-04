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

__attribute__((used)) static fInt fNaturalLog(fInt value)
{
	uint32_t i;
	fInt upper_bound = Divide(8, 1000);
	fInt fNegativeOne = ConvertToFraction(-1);
	fInt solution = ConvertToFraction(0); /*Starting off with baseline of 0 */
	fInt error_term;

	static const uint32_t k_array[10] = {160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078};
	static const uint32_t logk_array[10] = {27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78};

	while (GreaterThan(fAdd(value, fNegativeOne), upper_bound)) {
		for (i = 0; i < 10; i++) {
			if (GreaterThan(value, GetScaledFraction(k_array[i], 10000))) {
				value = fDivide(value, GetScaledFraction(k_array[i], 10000));
				solution = fAdd(solution, GetScaledFraction(logk_array[i], 10000));
			}
		}
	}

	error_term = fAdd(fNegativeOne, value);

	return (fAdd(solution, error_term));
}