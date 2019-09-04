#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipmmu_vmsa_domain {int /*<<< orphan*/  context_id; TYPE_1__* mmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMCTR ; 
 int /*<<< orphan*/  IMCTR_FLUSH ; 
 int /*<<< orphan*/  ipmmu_ctx_write_all (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmmu_domain_free_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmmu_tlb_sync (struct ipmmu_vmsa_domain*) ; 

__attribute__((used)) static void ipmmu_domain_destroy_context(struct ipmmu_vmsa_domain *domain)
{
	if (!domain->mmu)
		return;

	/*
	 * Disable the context. Flush the TLB as required when modifying the
	 * context registers.
	 *
	 * TODO: Is TLB flush really needed ?
	 */
	ipmmu_ctx_write_all(domain, IMCTR, IMCTR_FLUSH);
	ipmmu_tlb_sync(domain);
	ipmmu_domain_free_context(domain->mmu->root, domain->context_id);
}