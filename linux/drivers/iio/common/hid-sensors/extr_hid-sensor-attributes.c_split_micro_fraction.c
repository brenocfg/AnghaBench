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
 unsigned int int_pow (int,int) ; 

__attribute__((used)) static void split_micro_fraction(unsigned int no, int exp, int *val1, int *val2)
{
	int divisor = int_pow(10, exp);

	*val1 = no / divisor;
	*val2 = no % divisor * int_pow(10, 6 - exp);
}