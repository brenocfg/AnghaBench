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
typedef  int __u64 ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int PAGE_SIZE ; 

__attribute__((used)) static unsigned long get_ind_bit(__u64 addr, unsigned long bit_nr, bool swap)
{
	unsigned long bit;

	bit = bit_nr + (addr % PAGE_SIZE) * 8;

	return swap ? (bit ^ (BITS_PER_LONG - 1)) : bit;
}