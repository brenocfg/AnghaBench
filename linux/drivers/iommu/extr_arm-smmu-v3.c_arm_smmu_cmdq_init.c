#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_n_shift; } ;
struct TYPE_3__ {TYPE_2__ llq; } ;
struct arm_smmu_cmdq {int /*<<< orphan*/ * valid_map; int /*<<< orphan*/  lock; int /*<<< orphan*/  owner_prod; TYPE_1__ q; } ;
struct arm_smmu_device {int /*<<< orphan*/  dev; struct arm_smmu_cmdq cmdq; } ;
typedef  int /*<<< orphan*/  atomic_long_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  arm_smmu_cmdq_free_bitmap ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_zalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_add_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arm_smmu_cmdq_init(struct arm_smmu_device *smmu)
{
	int ret = 0;
	struct arm_smmu_cmdq *cmdq = &smmu->cmdq;
	unsigned int nents = 1 << cmdq->q.llq.max_n_shift;
	atomic_long_t *bitmap;

	atomic_set(&cmdq->owner_prod, 0);
	atomic_set(&cmdq->lock, 0);

	bitmap = (atomic_long_t *)bitmap_zalloc(nents, GFP_KERNEL);
	if (!bitmap) {
		dev_err(smmu->dev, "failed to allocate cmdq bitmap\n");
		ret = -ENOMEM;
	} else {
		cmdq->valid_map = bitmap;
		devm_add_action(smmu->dev, arm_smmu_cmdq_free_bitmap, bitmap);
	}

	return ret;
}