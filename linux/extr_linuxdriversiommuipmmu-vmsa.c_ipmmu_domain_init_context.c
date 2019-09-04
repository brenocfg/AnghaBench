#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_11__ {int* ttbr; int* mair; } ;
struct TYPE_15__ {int pgsize_bitmap; int ias; int oas; TYPE_3__ arm_lpae_s1_cfg; int /*<<< orphan*/  iommu_dev; int /*<<< orphan*/ * tlb; int /*<<< orphan*/  quirks; } ;
struct TYPE_9__ {int force_aperture; int /*<<< orphan*/  aperture_end; } ;
struct TYPE_10__ {TYPE_1__ geometry; } ;
struct ipmmu_vmsa_domain {int context_id; TYPE_5__* mmu; TYPE_8__ cfg; int /*<<< orphan*/  iop; TYPE_2__ io_domain; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {TYPE_4__* features; TYPE_6__* root; } ;
struct TYPE_12__ {scalar_t__ setup_imbuscr; scalar_t__ twobit_imttbcr_sl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_32_LPAE_S1 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IMBUSCR ; 
 int IMBUSCR_BUSSEL_MASK ; 
 int IMBUSCR_DVM ; 
 int /*<<< orphan*/  IMCTR ; 
 int IMCTR_FLUSH ; 
 int IMCTR_INTEN ; 
 int IMCTR_MMUEN ; 
 int /*<<< orphan*/  IMMAIR0 ; 
 int /*<<< orphan*/  IMSTR ; 
 int /*<<< orphan*/  IMTTBCR ; 
 int IMTTBCR_EAE ; 
 int IMTTBCR_IRGN0_WB_WA ; 
 int IMTTBCR_ORGN0_WB_WA ; 
 int IMTTBCR_SH0_INNER_SHAREABLE ; 
 int IMTTBCR_SL0_LVL_1 ; 
 int IMTTBCR_SL0_TWOBIT_LVL_1 ; 
 int /*<<< orphan*/  IMTTLBR0 ; 
 int /*<<< orphan*/  IMTTUBR0 ; 
 int /*<<< orphan*/  IO_PGTABLE_QUIRK_ARM_NS ; 
 int SZ_1G ; 
 int SZ_2M ; 
 int SZ_4K ; 
 int /*<<< orphan*/  alloc_io_pgtable_ops (int /*<<< orphan*/ ,TYPE_8__*,struct ipmmu_vmsa_domain*) ; 
 int ipmmu_ctx_read_root (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmmu_ctx_write_all (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipmmu_ctx_write_root (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ,int) ; 
 int ipmmu_domain_allocate_context (TYPE_6__*,struct ipmmu_vmsa_domain*) ; 
 int /*<<< orphan*/  ipmmu_domain_free_context (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ipmmu_gather_ops ; 

__attribute__((used)) static int ipmmu_domain_init_context(struct ipmmu_vmsa_domain *domain)
{
	u64 ttbr;
	u32 tmp;
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
	domain->cfg.tlb = &ipmmu_gather_ops;
	domain->io_domain.geometry.aperture_end = DMA_BIT_MASK(32);
	domain->io_domain.geometry.force_aperture = true;
	/*
	 * TODO: Add support for coherent walk through CCI with DVM and remove
	 * cache handling. For now, delegate it to the io-pgtable code.
	 */
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

	/* TTBR0 */
	ttbr = domain->cfg.arm_lpae_s1_cfg.ttbr[0];
	ipmmu_ctx_write_root(domain, IMTTLBR0, ttbr);
	ipmmu_ctx_write_root(domain, IMTTUBR0, ttbr >> 32);

	/*
	 * TTBCR
	 * We use long descriptors with inner-shareable WBWA tables and allocate
	 * the whole 32-bit VA space to TTBR0.
	 */
	if (domain->mmu->features->twobit_imttbcr_sl0)
		tmp = IMTTBCR_SL0_TWOBIT_LVL_1;
	else
		tmp = IMTTBCR_SL0_LVL_1;

	ipmmu_ctx_write_root(domain, IMTTBCR, IMTTBCR_EAE |
			     IMTTBCR_SH0_INNER_SHAREABLE | IMTTBCR_ORGN0_WB_WA |
			     IMTTBCR_IRGN0_WB_WA | tmp);

	/* MAIR0 */
	ipmmu_ctx_write_root(domain, IMMAIR0,
			     domain->cfg.arm_lpae_s1_cfg.mair[0]);

	/* IMBUSCR */
	if (domain->mmu->features->setup_imbuscr)
		ipmmu_ctx_write_root(domain, IMBUSCR,
				     ipmmu_ctx_read_root(domain, IMBUSCR) &
				     ~(IMBUSCR_DVM | IMBUSCR_BUSSEL_MASK));

	/*
	 * IMSTR
	 * Clear all interrupt flags.
	 */
	ipmmu_ctx_write_root(domain, IMSTR, ipmmu_ctx_read_root(domain, IMSTR));

	/*
	 * IMCTR
	 * Enable the MMU and interrupt generation. The long-descriptor
	 * translation table format doesn't use TEX remapping. Don't enable AF
	 * software management as we have no use for it. Flush the TLB as
	 * required when modifying the context registers.
	 */
	ipmmu_ctx_write_all(domain, IMCTR,
			    IMCTR_INTEN | IMCTR_FLUSH | IMCTR_MMUEN);

	return 0;
}