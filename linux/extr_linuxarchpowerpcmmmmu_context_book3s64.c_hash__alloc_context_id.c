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

/* Variables and functions */
 unsigned long MAX_USER_CONTEXT ; 
 unsigned long MAX_USER_CONTEXT_65BIT_VA ; 
 int /*<<< orphan*/  MIN_USER_CONTEXT ; 
 int /*<<< orphan*/  MMU_FTR_68_BIT_VA ; 
 int alloc_context_id (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 

int hash__alloc_context_id(void)
{
	unsigned long max;

	if (mmu_has_feature(MMU_FTR_68_BIT_VA))
		max = MAX_USER_CONTEXT;
	else
		max = MAX_USER_CONTEXT_65BIT_VA;

	return alloc_context_id(MIN_USER_CONTEXT, max);
}