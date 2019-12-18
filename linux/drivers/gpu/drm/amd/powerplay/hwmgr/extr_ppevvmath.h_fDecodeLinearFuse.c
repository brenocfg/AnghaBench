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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  fInt ;

/* Variables and functions */
 int /*<<< orphan*/  Convert_ULONG_ToFraction (scalar_t__) ; 
 int /*<<< orphan*/  fAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fDivide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uPow (int,scalar_t__) ; 

__attribute__((used)) static fInt fDecodeLinearFuse(uint32_t fuse_value, fInt f_min, fInt f_range, uint32_t bitlength)
{
	fInt f_fuse_value = Convert_ULONG_ToFraction(fuse_value);
	fInt f_bit_max_value = Convert_ULONG_ToFraction((uPow(2, bitlength)) - 1);

	fInt f_decoded_value;

	f_decoded_value = fDivide(f_fuse_value, f_bit_max_value);
	f_decoded_value = fMultiply(f_decoded_value, f_range);
	f_decoded_value = fAdd(f_decoded_value, f_min);

	return f_decoded_value;
}