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
typedef  long u32 ;

/* Variables and functions */
 scalar_t__ upper_32_bits (long) ; 

__attribute__((used)) static int
is_MSB_are_same(long reply_pool_start_address, u32 pool_sz)
{
	long reply_pool_end_address;

	reply_pool_end_address = reply_pool_start_address + pool_sz;

	if (upper_32_bits(reply_pool_start_address) ==
		upper_32_bits(reply_pool_end_address))
		return 1;
	else
		return 0;
}