#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pgsize_bitmap; int ias; int oas; int coherent_walk; int /*<<< orphan*/  iommu_dev; int /*<<< orphan*/ * tlb; int /*<<< orphan*/  quirks; } ;
struct TYPE_7__ {int force_aperture; int /*<<< orphan*/  aperture_end; } ;
struct TYPE_8__ {TYPE_1__ geometry; } ;
struct ipmmu_vmsa_domain {int context_id; TYPE_3__* mmu; int /*<<< orphan*/  iop; TYPE_6__ cfg; TYPE_2__ io_domain; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_4__* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_32_LPAE_S1 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IO_PGTABLE_QUIRK_ARM_NS ; 
 int SZ_1G ; 
 int SZ_2M ; 
 int SZ_4K ; 
 int /*<<< orphan*/  alloc_io_pgtable_ops (int /*<<< orphan*/ ,TYPE_6__*,struct ipmmu_vmsa_domain*) ; 
 int ipmmu_domain_allocate_context (TYPE_4__*,struct ipmmu_vmsa_domain*) ; 
 int /*<<< orphan*/  ipmmu_domain_free_context (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ipmmu_domain_setup_context (struct ipmmu_vmsa_domain*) ; 
 int /*<<< orphan*/  ipmmu_flush_ops ; 

__attribute__((used)) static int ipmmu_domain_init_context(struct ipmmu_vmsa_domain *domain)
{
	int ret;

	/*
	 * Allocate the page table operations.
	 *
	 * VMSA states in section B3.6.3 "Control of Secure or Non-secure memory
	 * access, Long-descriptor format" that the NStable bit being set in a
	 * table descriptor will result in the NStable and NS bits of all child
	 * entries being ignored and considered as being set. The IPMMU seems
	 * not to comply with this, as it generates a secure access page fault
	 * if any of the NStable and NS bits isn't set when running in
	 * non-secure mode.
	 */
	domain->cfg.quirks = IO_PGTABLE_QUIRK_ARM_NS;
	domain->cfg.pgsize_bitmap = SZ_1G | SZ_2M | SZ_4K;
	domain->cfg.ias = 32;
	domain->cfg.oas = 40;
	domain->cfg.tlb = &ipmmu_flush_ops;
	domain->io_domain.geometry.aperture_end = DMA_BIT_MASK(32);
	domain->io_domain.geometry.force_aperture = true;
	/*
	 * TODO: Add support for coherent walk through CCI with DVM and remove
	 * cache handling. For now, delegate it to the io-pgtable code.
	 */
	domain->cfg.coherent_walk = false;
	domain->cfg.iommu_dev = domain->mmu->root->dev;

	/*
	 * Find an unused context.
	 */
	ret = ipmmu_domain_allocate_context(domain->mmu->root, domain);
	if (ret < 0)
		return ret;

	domain->context_id = ret;

	domain->iop = alloc_io_pgtable_ops(ARM_32_LPAE_S1, &domain->cfg,
					   domain);
	if (!domain->iop) {
		ipmmu_domain_free_context(domain->mmu->root,
					  domain->context_id);
		return -EINVAL;
	}

	ipmmu_domain_setup_context(domain);
	return 0;
}