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
 int FLAGS_MASK ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_oblock (int) ; 

__attribute__((used)) static void unpack_value(__le64 value_le, dm_oblock_t *block, unsigned *flags)
{
	uint64_t value = le64_to_cpu(value_le);
	uint64_t b = value >> 16;
	*block = to_oblock(b);
	*flags = value & FLAGS_MASK;
}