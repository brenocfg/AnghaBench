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
 int /*<<< orphan*/  ASSERT (unsigned long long) ; 
 unsigned long long div64_u64_rem (unsigned long long,unsigned long long,unsigned long long*) ; 

__attribute__((used)) static inline unsigned long long complete_integer_division_u64(
	unsigned long long dividend,
	unsigned long long divisor,
	unsigned long long *remainder)
{
	unsigned long long result;

	ASSERT(divisor);

	result = div64_u64_rem(dividend, divisor, remainder);

	return result;
}