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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  __ttm_kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 

void ttm_kunmap_atomic_prot(void *addr, pgprot_t prot)
{
	if (pgprot_val(prot) == pgprot_val(PAGE_KERNEL))
		kunmap_atomic(addr);
	else
		__ttm_kunmap_atomic(addr);
}