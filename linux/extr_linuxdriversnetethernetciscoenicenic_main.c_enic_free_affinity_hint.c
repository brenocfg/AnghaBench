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
struct enic {int intr_count; TYPE_1__* msix; } ;
struct TYPE_2__ {int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 scalar_t__ enic_is_err_intr (struct enic*,int) ; 
 scalar_t__ enic_is_notify_intr (struct enic*,int) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_free_affinity_hint(struct enic *enic)
{
	int i;

	for (i = 0; i < enic->intr_count; i++) {
		if (enic_is_err_intr(enic, i) || enic_is_notify_intr(enic, i))
			continue;
		free_cpumask_var(enic->msix[i].affinity_mask);
	}
}