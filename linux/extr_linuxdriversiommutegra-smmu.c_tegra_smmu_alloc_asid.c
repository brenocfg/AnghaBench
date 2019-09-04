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
struct tegra_smmu {int /*<<< orphan*/  lock; int /*<<< orphan*/  asids; TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned long num_asids; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_smmu_alloc_asid(struct tegra_smmu *smmu, unsigned int *idp)
{
	unsigned long id;

	mutex_lock(&smmu->lock);

	id = find_first_zero_bit(smmu->asids, smmu->soc->num_asids);
	if (id >= smmu->soc->num_asids) {
		mutex_unlock(&smmu->lock);
		return -ENOSPC;
	}

	set_bit(id, smmu->asids);
	*idp = id;

	mutex_unlock(&smmu->lock);
	return 0;
}