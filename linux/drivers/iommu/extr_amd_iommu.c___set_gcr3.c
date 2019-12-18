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
typedef  unsigned long u64 ;
struct protection_domain {scalar_t__ mode; int /*<<< orphan*/  glx; int /*<<< orphan*/  gcr3_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned long GCR3_VALID ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_MODE_NONE ; 
 int __amd_iommu_flush_tlb (struct protection_domain*,int) ; 
 unsigned long* __get_gcr3_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __set_gcr3(struct protection_domain *domain, int pasid,
		      unsigned long cr3)
{
	u64 *pte;

	if (domain->mode != PAGE_MODE_NONE)
		return -EINVAL;

	pte = __get_gcr3_pte(domain->gcr3_tbl, domain->glx, pasid, true);
	if (pte == NULL)
		return -ENOMEM;

	*pte = (cr3 & PAGE_MASK) | GCR3_VALID;

	return __amd_iommu_flush_tlb(domain, pasid);
}