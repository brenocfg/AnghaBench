#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_3__ {int /*<<< orphan*/  p2m_generation; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* HYPERVISOR_shared_info ; 
 int PAGE_SHIFT ; 
 int PMDS_PER_MID_PAGE ; 
 int PMD_SIZE ; 
 int _KERNPG_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 int /*<<< orphan*/ * alloc_p2m_page () ; 
 int /*<<< orphan*/  copy_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_p2m_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/ * lookup_pmd_address (unsigned long) ; 
 int /*<<< orphan*/  p2m_update_lock ; 
 int /*<<< orphan*/  paravirt_alloc_pte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  paravirt_release_pte (int) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static pte_t *alloc_p2m_pmd(unsigned long addr, pte_t *pte_pg)
{
	pte_t *ptechk;
	pte_t *pte_newpg[PMDS_PER_MID_PAGE];
	pmd_t *pmdp;
	unsigned int level;
	unsigned long flags;
	unsigned long vaddr;
	int i;

	/* Do all allocations first to bail out in error case. */
	for (i = 0; i < PMDS_PER_MID_PAGE; i++) {
		pte_newpg[i] = alloc_p2m_page();
		if (!pte_newpg[i]) {
			for (i--; i >= 0; i--)
				free_p2m_page(pte_newpg[i]);

			return NULL;
		}
	}

	vaddr = addr & ~(PMD_SIZE * PMDS_PER_MID_PAGE - 1);

	for (i = 0; i < PMDS_PER_MID_PAGE; i++) {
		copy_page(pte_newpg[i], pte_pg);
		paravirt_alloc_pte(&init_mm, __pa(pte_newpg[i]) >> PAGE_SHIFT);

		pmdp = lookup_pmd_address(vaddr);
		BUG_ON(!pmdp);

		spin_lock_irqsave(&p2m_update_lock, flags);

		ptechk = lookup_address(vaddr, &level);
		if (ptechk == pte_pg) {
			HYPERVISOR_shared_info->arch.p2m_generation++;
			wmb(); /* Tools are synchronizing via p2m_generation. */
			set_pmd(pmdp,
				__pmd(__pa(pte_newpg[i]) | _KERNPG_TABLE));
			wmb(); /* Tools are synchronizing via p2m_generation. */
			HYPERVISOR_shared_info->arch.p2m_generation++;
			pte_newpg[i] = NULL;
		}

		spin_unlock_irqrestore(&p2m_update_lock, flags);

		if (pte_newpg[i]) {
			paravirt_release_pte(__pa(pte_newpg[i]) >> PAGE_SHIFT);
			free_p2m_page(pte_newpg[i]);
		}

		vaddr += PMD_SIZE;
	}

	return lookup_address(addr, &level);
}