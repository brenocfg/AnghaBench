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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vtcr; int /*<<< orphan*/  vttbr; } ;
struct io_pgtable_cfg {TYPE_1__ arm_lpae_s2_cfg; } ;
struct arm_smmu_s2_cfg {int /*<<< orphan*/  vtcr; int /*<<< orphan*/  vttbr; int /*<<< orphan*/  vmid; } ;
struct arm_smmu_domain {struct arm_smmu_s2_cfg s2_cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  vmid_bits; int /*<<< orphan*/  vmid_map; } ;

/* Variables and functions */
 int arm_smmu_bitmap_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_domain_finalise_s2(struct arm_smmu_domain *smmu_domain,
				       struct io_pgtable_cfg *pgtbl_cfg)
{
	int vmid;
	struct arm_smmu_device *smmu = smmu_domain->smmu;
	struct arm_smmu_s2_cfg *cfg = &smmu_domain->s2_cfg;

	vmid = arm_smmu_bitmap_alloc(smmu->vmid_map, smmu->vmid_bits);
	if (vmid < 0)
		return vmid;

	cfg->vmid	= (u16)vmid;
	cfg->vttbr	= pgtbl_cfg->arm_lpae_s2_cfg.vttbr;
	cfg->vtcr	= pgtbl_cfg->arm_lpae_s2_cfg.vtcr;
	return 0;
}