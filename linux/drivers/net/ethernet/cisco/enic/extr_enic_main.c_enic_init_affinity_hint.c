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
struct enic {int intr_count; TYPE_1__* msix; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cpumask_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 scalar_t__ enic_is_err_intr (struct enic*,int) ; 
 scalar_t__ enic_is_notify_intr (struct enic*,int) ; 
 scalar_t__ zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_init_affinity_hint(struct enic *enic)
{
	int numa_node = dev_to_node(&enic->pdev->dev);
	int i;

	for (i = 0; i < enic->intr_count; i++) {
		if (enic_is_err_intr(enic, i) || enic_is_notify_intr(enic, i) ||
		    (cpumask_available(enic->msix[i].affinity_mask) &&
		     !cpumask_empty(enic->msix[i].affinity_mask)))
			continue;
		if (zalloc_cpumask_var(&enic->msix[i].affinity_mask,
				       GFP_KERNEL))
			cpumask_set_cpu(cpumask_local_spread(i, numa_node),
					enic->msix[i].affinity_mask);
	}
}