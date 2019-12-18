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
 int /*<<< orphan*/  ASSERT (int) ; 
 int BW_FIXED_BITS_PER_FRACTIONAL_PART ; 
 int BW_FIXED_MAX_I32 ; 
 int BW_FIXED_MIN_I32 ; 

struct bw_fixed bw_int_to_fixed_nonconst(int64_t value)
{
	struct bw_fixed res;
	ASSERT(value < BW_FIXED_MAX_I32 && value > BW_FIXED_MIN_I32);
	res.value = value << BW_FIXED_BITS_PER_FRACTIONAL_PART;
	return res;
}