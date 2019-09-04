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
 int /*<<< orphan*/  cpu_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_dc_aliases ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tx39_blast_dcache () ; 

__attribute__((used)) static void tx39_flush_cache_range(struct vm_area_struct *vma,
	unsigned long start, unsigned long end)
{
	if (!cpu_has_dc_aliases)
		return;
	if (!(cpu_context(smp_processor_id(), vma->vm_mm)))
		return;

	tx39_blast_dcache();
}