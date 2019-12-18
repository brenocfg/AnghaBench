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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dsu_pmu {int num_counters; int /*<<< orphan*/  pmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dsu_pmu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dsu_pmu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dsu_pmu *dsu_pmu_alloc(struct platform_device *pdev)
{
	struct dsu_pmu *dsu_pmu;

	dsu_pmu = devm_kzalloc(&pdev->dev, sizeof(*dsu_pmu), GFP_KERNEL);
	if (!dsu_pmu)
		return ERR_PTR(-ENOMEM);

	raw_spin_lock_init(&dsu_pmu->pmu_lock);
	/*
	 * Initialise the number of counters to -1, until we probe
	 * the real number on a connected CPU.
	 */
	dsu_pmu->num_counters = -1;
	return dsu_pmu;
}