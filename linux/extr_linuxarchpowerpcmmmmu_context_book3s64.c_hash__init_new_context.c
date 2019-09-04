#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int hash__alloc_context_id () ; 
 int /*<<< orphan*/  pkey_mm_init (struct mm_struct*) ; 
 int /*<<< orphan*/  slice_init_new_context_exec (struct mm_struct*) ; 
 int /*<<< orphan*/  subpage_prot_init_new_context (struct mm_struct*) ; 

__attribute__((used)) static int hash__init_new_context(struct mm_struct *mm)
{
	int index;

	index = hash__alloc_context_id();
	if (index < 0)
		return index;

	/*
	 * The old code would re-promote on fork, we don't do that when using
	 * slices as it could cause problem promoting slices that have been
	 * forced down to 4K.
	 *
	 * For book3s we have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details for newly allocated mm's (which will
	 * have id == 0) and don't alter context slice inherited via fork (which
	 * will have id != 0).
	 *
	 * We should not be calling init_new_context() on init_mm. Hence a
	 * check against 0 is OK.
	 */
	if (mm->context.id == 0)
		slice_init_new_context_exec(mm);

	subpage_prot_init_new_context(mm);

	pkey_mm_init(mm);
	return index;
}