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
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 unsigned int FLAGS_MASK ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int from_oblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le64 pack_value(dm_oblock_t block, unsigned flags)
{
	uint64_t value = from_oblock(block);
	value <<= 16;
	value = value | (flags & FLAGS_MASK);
	return cpu_to_le64(value);
}