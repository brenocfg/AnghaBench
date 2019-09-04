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
struct arm_smmu_queue {int max_n_shift; int base_dma; size_t ent_dwords; int q_base; scalar_t__ cons; scalar_t__ prod; void* cons_reg; void* prod_reg; int /*<<< orphan*/  base; } ;
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int Q_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  Q_BASE_LOG2SIZE ; 
 int Q_BASE_RWA ; 
 void* arm_smmu_page1_fixup (unsigned long,struct arm_smmu_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ ,size_t,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_init_one_queue(struct arm_smmu_device *smmu,
				   struct arm_smmu_queue *q,
				   unsigned long prod_off,
				   unsigned long cons_off,
				   size_t dwords)
{
	size_t qsz = ((1 << q->max_n_shift) * dwords) << 3;

	q->base = dmam_alloc_coherent(smmu->dev, qsz, &q->base_dma, GFP_KERNEL);
	if (!q->base) {
		dev_err(smmu->dev, "failed to allocate queue (0x%zx bytes)\n",
			qsz);
		return -ENOMEM;
	}

	q->prod_reg	= arm_smmu_page1_fixup(prod_off, smmu);
	q->cons_reg	= arm_smmu_page1_fixup(cons_off, smmu);
	q->ent_dwords	= dwords;

	q->q_base  = Q_BASE_RWA;
	q->q_base |= q->base_dma & Q_BASE_ADDR_MASK;
	q->q_base |= FIELD_PREP(Q_BASE_LOG2SIZE, q->max_n_shift);

	q->prod = q->cons = 0;
	return 0;
}