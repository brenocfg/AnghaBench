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

__attribute__((used)) static unsigned int mt9v032_calc_ratio(unsigned int input, unsigned int output)
{
	/* Compute the power-of-two binning factor closest to the input size to
	 * output size ratio. Given that the output size is bounded by input/4
	 * and input, a generic implementation would be an ineffective luxury.
	 */
	if (output * 3 > input * 2)
		return 1;
	if (output * 3 > input)
		return 2;
	return 4;
}