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
struct iommu_domain {int dummy; } ;
struct arm_smmu_s2_cfg {scalar_t__ vmid; } ;
struct TYPE_2__ {scalar_t__ asid; } ;
struct arm_smmu_s1_cfg {TYPE_1__ cd; int /*<<< orphan*/  cdptr_dma; scalar_t__ cdptr; } ;
struct arm_smmu_domain {scalar_t__ stage; struct arm_smmu_s2_cfg s2_cfg; struct arm_smmu_device* smmu; struct arm_smmu_s1_cfg s1_cfg; int /*<<< orphan*/  pgtbl_ops; } ;
struct arm_smmu_device {int /*<<< orphan*/  vmid_map; int /*<<< orphan*/  asid_map; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_DOMAIN_S1 ; 
 int CTXDESC_CD_DWORDS ; 
 int /*<<< orphan*/  arm_smmu_bitmap_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_io_pgtable_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct arm_smmu_domain*) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void arm_smmu_domain_free(struct iommu_domain *domain)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	struct arm_smmu_device *smmu = smmu_domain->smmu;

	iommu_put_dma_cookie(domain);
	free_io_pgtable_ops(smmu_domain->pgtbl_ops);

	/* Free the CD and ASID, if we allocated them */
	if (smmu_domain->stage == ARM_SMMU_DOMAIN_S1) {
		struct arm_smmu_s1_cfg *cfg = &smmu_domain->s1_cfg;

		if (cfg->cdptr) {
			dmam_free_coherent(smmu_domain->smmu->dev,
					   CTXDESC_CD_DWORDS << 3,
					   cfg->cdptr,
					   cfg->cdptr_dma);

			arm_smmu_bitmap_free(smmu->asid_map, cfg->cd.asid);
		}
	} else {
		struct arm_smmu_s2_cfg *cfg = &smmu_domain->s2_cfg;
		if (cfg->vmid)
			arm_smmu_bitmap_free(smmu->vmid_map, cfg->vmid);
	}

	kfree(smmu_domain);
}