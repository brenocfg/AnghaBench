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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRK_BUG ; 
 int /*<<< orphan*/  uasm_i_break (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jit_fill_hole(void *area, unsigned int size)
{
	u32 *p;

	/* We are guaranteed to have aligned memory. */
	for (p = area; size >= sizeof(u32); size -= sizeof(u32))
		uasm_i_break(&p, BRK_BUG); /* Increments p */
}