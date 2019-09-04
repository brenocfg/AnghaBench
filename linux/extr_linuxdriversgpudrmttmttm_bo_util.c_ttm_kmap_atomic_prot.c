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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __ttm_kmap_atomic_prot (struct page*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 

void *ttm_kmap_atomic_prot(struct page *page, pgprot_t prot)
{
	if (pgprot_val(prot) == pgprot_val(PAGE_KERNEL))
		return kmap_atomic(page);
	else
		return __ttm_kmap_atomic_prot(page, prot);
}