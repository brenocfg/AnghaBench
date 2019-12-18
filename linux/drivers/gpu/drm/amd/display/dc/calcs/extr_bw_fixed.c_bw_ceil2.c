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
struct bw_fixed {int value; } ;
typedef  int int64_t ;

/* Variables and functions */
 int abs_i64 (int) ; 
 int div64_s64 (int,int) ; 

struct bw_fixed bw_ceil2(
	const struct bw_fixed arg,
	const struct bw_fixed significance)
{
	struct bw_fixed result;
	int64_t multiplicand;

	multiplicand = div64_s64(arg.value, abs_i64(significance.value));
	result.value = abs_i64(significance.value) * multiplicand;
	if (abs_i64(result.value) < abs_i64(arg.value)) {
		if (arg.value < 0)
			result.value -= abs_i64(significance.value);
		else
			result.value += abs_i64(significance.value);
	}
	return result;
}