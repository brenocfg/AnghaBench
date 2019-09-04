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
typedef  int instr ;

/* Variables and functions */
 int STK_ALLOC_1M ; 
 int /*<<< orphan*/  STK_ALLOC_MATCH (int) ; 

__attribute__((used)) static long
stack_increment(instr * prologue_pc)
{
	while (!STK_ALLOC_MATCH(*prologue_pc))
		++prologue_pc;

	/* Count the bytes allocated. */
	if ((*prologue_pc & STK_ALLOC_1M) == STK_ALLOC_1M)
		return -(((long)(*prologue_pc) << 48) >> 48);
	else
		return (*prologue_pc >> 13) & 0xff;
}