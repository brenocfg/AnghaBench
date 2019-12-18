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
struct pci_dev {int dummy; } ;
struct arm_smmu_master {int /*<<< orphan*/  dev; int /*<<< orphan*/  ats_enabled; struct arm_smmu_domain* domain; struct arm_smmu_device* smmu; } ;
struct arm_smmu_domain {int /*<<< orphan*/  nr_ats_masters; } ;
struct arm_smmu_device {int /*<<< orphan*/  pgsize_bitmap; } ;

/* Variables and functions */
 size_t __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_atc_inv_domain (struct arm_smmu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ pci_enable_ats (struct pci_dev*,size_t) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_smmu_enable_ats(struct arm_smmu_master *master)
{
	size_t stu;
	struct pci_dev *pdev;
	struct arm_smmu_device *smmu = master->smmu;
	struct arm_smmu_domain *smmu_domain = master->domain;

	/* Don't enable ATS at the endpoint if it's not enabled in the STE */
	if (!master->ats_enabled)
		return;

	/* Smallest Translation Unit: log2 of the smallest supported granule */
	stu = __ffs(smmu->pgsize_bitmap);
	pdev = to_pci_dev(master->dev);

	atomic_inc(&smmu_domain->nr_ats_masters);
	arm_smmu_atc_inv_domain(smmu_domain, 0, 0, 0);
	if (pci_enable_ats(pdev, stu))
		dev_err(master->dev, "Failed to enable ATS (STU %zu)\n", stu);
}