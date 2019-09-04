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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PGALLOC_GFP ; 
 scalar_t__ PGD_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_cache ; 

pgd_t *pgd_alloc(struct mm_struct *mm)
{
	if (PGD_SIZE == PAGE_SIZE)
		return (pgd_t *)__get_free_page(PGALLOC_GFP);
	else
		return kmem_cache_alloc(pgd_cache, PGALLOC_GFP);
}