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
typedef  int /*<<< orphan*/  instr ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STK_ALLOC_MATCH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static instr *
seek_prologue(instr * pc)
{
	while (!STK_ALLOC_MATCH(*pc))
		--pc;
	while (!BB_END(*(pc - 1)))
		--pc;
	return pc;
}