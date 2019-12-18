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
typedef  int const u8 ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 

bool qtnf_utils_is_bit_set(const u8 *arr, unsigned int bit,
			   unsigned int arr_max_len)
{
	unsigned int idx = bit / BITS_PER_BYTE;
	u8 mask = 1 << (bit - (idx * BITS_PER_BYTE));

	if (idx >= arr_max_len)
		return false;

	return arr[idx] & mask;
}