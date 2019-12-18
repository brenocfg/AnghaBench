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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ apply_to_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_mapped_fn ; 

__attribute__((used)) static int privcmd_vma_range_is_mapped(
	           struct vm_area_struct *vma,
	           unsigned long addr,
	           unsigned long nr_pages)
{
	return apply_to_page_range(vma->vm_mm, addr, nr_pages << PAGE_SHIFT,
				   is_mapped_fn, NULL) != 0;
}