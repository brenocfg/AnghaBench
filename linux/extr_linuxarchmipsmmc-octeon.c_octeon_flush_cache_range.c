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
struct vm_area_struct {int vm_flags; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  octeon_flush_icache_all_cores (struct vm_area_struct*) ; 

__attribute__((used)) static void octeon_flush_cache_range(struct vm_area_struct *vma,
				     unsigned long start, unsigned long end)
{
	if (vma->vm_flags & VM_EXEC)
		octeon_flush_icache_all_cores(vma);
}