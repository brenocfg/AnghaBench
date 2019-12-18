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
typedef  int u32 ;
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {int cbndx; } ;
struct arm_smmu_domain {TYPE_1__ cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_FAR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_FSR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_FSYNR0 ; 
 int /*<<< orphan*/  ARM_SMMU_GR1_CBFRSYNRA (int) ; 
 int FSR_FAULT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int arm_smmu_cb_read (struct arm_smmu_device*,int,int /*<<< orphan*/ ) ; 
 unsigned long arm_smmu_cb_readq (struct arm_smmu_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_cb_write (struct arm_smmu_device*,int,int /*<<< orphan*/ ,int) ; 
 int arm_smmu_gr1_read (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,unsigned long,int,int,int) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static irqreturn_t arm_smmu_context_fault(int irq, void *dev)
{
	u32 fsr, fsynr, cbfrsynra;
	unsigned long iova;
	struct iommu_domain *domain = dev;
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	struct arm_smmu_device *smmu = smmu_domain->smmu;
	int idx = smmu_domain->cfg.cbndx;

	fsr = arm_smmu_cb_read(smmu, idx, ARM_SMMU_CB_FSR);
	if (!(fsr & FSR_FAULT))
		return IRQ_NONE;

	fsynr = arm_smmu_cb_read(smmu, idx, ARM_SMMU_CB_FSYNR0);
	iova = arm_smmu_cb_readq(smmu, idx, ARM_SMMU_CB_FAR);
	cbfrsynra = arm_smmu_gr1_read(smmu, ARM_SMMU_GR1_CBFRSYNRA(idx));

	dev_err_ratelimited(smmu->dev,
	"Unhandled context fault: fsr=0x%x, iova=0x%08lx, fsynr=0x%x, cbfrsynra=0x%x, cb=%d\n",
			    fsr, iova, fsynr, cbfrsynra, idx);

	arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_FSR, fsr);
	return IRQ_HANDLED;
}