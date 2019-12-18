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

/* Variables and functions */

__attribute__((used)) static int mapM(int srcMin, int srcMax, int srcVal, int dstMin, int dstMax,
		int *dstVal)
{
	int numerator;
	int denominator;
	int quotient;

	if ((srcMin == srcMax) || (srcVal < srcMin) || (srcVal > srcMax))
		return -1;
	/*
	 * This is the overall expression used:
	 * *dstVal =
	 *   (srcVal - srcMin)*(dstMax - dstMin) / (srcMax - srcMin) + dstMin;
	 * but we need to account for rounding so below we use the modulus
	 * operator to find the remainder and increment if necessary.
	 */
	numerator = (srcVal - srcMin) * (dstMax - dstMin);
	denominator = srcMax - srcMin;
	quotient = numerator / denominator;

	if (2 * (numerator % denominator) >= denominator)
		quotient++;

	*dstVal = quotient + dstMin;

	return 0;
}