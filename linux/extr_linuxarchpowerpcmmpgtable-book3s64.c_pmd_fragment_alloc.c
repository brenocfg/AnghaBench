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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __alloc_for_pmdcache (struct mm_struct*) ; 
 int /*<<< orphan*/ * get_pmd_from_cache (struct mm_struct*) ; 

pmd_t *pmd_fragment_alloc(struct mm_struct *mm, unsigned long vmaddr)
{
	pmd_t *pmd;

	pmd = get_pmd_from_cache(mm);
	if (pmd)
		return pmd;

	return __alloc_for_pmdcache(mm);
}