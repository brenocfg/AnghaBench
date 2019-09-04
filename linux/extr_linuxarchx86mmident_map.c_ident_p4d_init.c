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
struct x86_mapping_info {int kernpg_flag; int /*<<< orphan*/  context; scalar_t__ (* alloc_pgt_page ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long P4D_MASK ; 
 unsigned long P4D_SIZE ; 
 int /*<<< orphan*/  __p4d (int) ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ident_pud_init (struct x86_mapping_info*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int p4d_index (unsigned long) ; 
 scalar_t__ p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_p4d (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ident_p4d_init(struct x86_mapping_info *info, p4d_t *p4d_page,
			  unsigned long addr, unsigned long end)
{
	unsigned long next;

	for (; addr < end; addr = next) {
		p4d_t *p4d = p4d_page + p4d_index(addr);
		pud_t *pud;

		next = (addr & P4D_MASK) + P4D_SIZE;
		if (next > end)
			next = end;

		if (p4d_present(*p4d)) {
			pud = pud_offset(p4d, 0);
			ident_pud_init(info, pud, addr, next);
			continue;
		}
		pud = (pud_t *)info->alloc_pgt_page(info->context);
		if (!pud)
			return -ENOMEM;
		ident_pud_init(info, pud, addr, next);
		set_p4d(p4d, __p4d(__pa(pud) | info->kernpg_flag));
	}

	return 0;
}