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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 unsigned int ENTRIES_SHIFT ; 
 int WORD_MASK_HIGH ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned dm_bitmap_word_used(void *addr, unsigned b)
{
	__le64 *words_le = addr;
	__le64 *w_le = words_le + (b >> ENTRIES_SHIFT);

	uint64_t bits = le64_to_cpu(*w_le);
	uint64_t mask = (bits + WORD_MASK_HIGH + 1) & WORD_MASK_HIGH;

	return !(~bits & mask);
}