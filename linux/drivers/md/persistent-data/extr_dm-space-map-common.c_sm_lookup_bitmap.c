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
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENTRIES_PER_WORD ; 
 unsigned int ENTRIES_SHIFT ; 
 int /*<<< orphan*/  test_bit_le (unsigned int,void*) ; 

__attribute__((used)) static unsigned sm_lookup_bitmap(void *addr, unsigned b)
{
	__le64 *words_le = addr;
	__le64 *w_le = words_le + (b >> ENTRIES_SHIFT);
	unsigned hi, lo;

	b = (b & (ENTRIES_PER_WORD - 1)) << 1;
	hi = !!test_bit_le(b, (void *) w_le);
	lo = !!test_bit_le(b + 1, (void *) w_le);
	return (hi << 1) | lo;
}