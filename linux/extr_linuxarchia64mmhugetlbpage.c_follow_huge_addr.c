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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long HPAGE_MASK ; 
 int /*<<< orphan*/  HPAGE_SIZE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ REGION_NUMBER (unsigned long) ; 
 scalar_t__ RGN_HPAGE ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 

struct page *follow_huge_addr(struct mm_struct *mm, unsigned long addr, int write)
{
	struct page *page;
	pte_t *ptep;

	if (REGION_NUMBER(addr) != RGN_HPAGE)
		return ERR_PTR(-EINVAL);

	ptep = huge_pte_offset(mm, addr, HPAGE_SIZE);
	if (!ptep || pte_none(*ptep))
		return NULL;
	page = pte_page(*ptep);
	page += ((addr & ~HPAGE_MASK) >> PAGE_SHIFT);
	return page;
}