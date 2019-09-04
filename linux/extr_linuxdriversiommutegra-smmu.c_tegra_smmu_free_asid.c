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
struct tegra_smmu {int /*<<< orphan*/  lock; int /*<<< orphan*/  asids; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_smmu_free_asid(struct tegra_smmu *smmu, unsigned int id)
{
	mutex_lock(&smmu->lock);
	clear_bit(id, smmu->asids);
	mutex_unlock(&smmu->lock);
}