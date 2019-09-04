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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ptep_set_access_flags (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pte_locked (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mmu_virtual_psize ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_access_flags_filter (int /*<<< orphan*/ ,struct vm_area_struct*,int) ; 

int ptep_set_access_flags(struct vm_area_struct *vma, unsigned long address,
			  pte_t *ptep, pte_t entry, int dirty)
{
	int changed;
	entry = set_access_flags_filter(entry, vma, dirty);
	changed = !pte_same(*(ptep), entry);
	if (changed) {
		assert_pte_locked(vma->vm_mm, address);
		__ptep_set_access_flags(vma, ptep, entry,
					address, mmu_virtual_psize);
	}
	return changed;
}