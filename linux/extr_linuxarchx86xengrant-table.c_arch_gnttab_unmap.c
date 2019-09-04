#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** ptes; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** ptes; TYPE_1__* area; } ;
struct TYPE_4__ {void* addr; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 TYPE_3__ gnttab_shared_vm_area ; 
 TYPE_2__ gnttab_status_vm_area ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void arch_gnttab_unmap(void *shared, unsigned long nr_gframes)
{
	pte_t **ptes;
	unsigned long addr;
	unsigned long i;

	if (shared == gnttab_status_vm_area.area->addr)
		ptes = gnttab_status_vm_area.ptes;
	else
		ptes = gnttab_shared_vm_area.ptes;

	addr = (unsigned long)shared;

	for (i = 0; i < nr_gframes; i++) {
		set_pte_at(&init_mm, addr, ptes[i], __pte(0));
		addr += PAGE_SIZE;
	}
}