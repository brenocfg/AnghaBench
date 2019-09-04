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
struct enic {int intr_count; int wq_count; TYPE_2__* msix; int /*<<< orphan*/  netdev; TYPE_1__* msix_entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  affinity_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 scalar_t__ cpumask_available (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ enic_is_err_intr (struct enic*,int) ; 
 scalar_t__ enic_is_notify_intr (struct enic*,int) ; 
 int enic_msix_wq_intr (struct enic*,int) ; 
 int irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enic_set_affinity_hint(struct enic *enic)
{
	int i;
	int err;

	for (i = 0; i < enic->intr_count; i++) {
		if (enic_is_err_intr(enic, i)		||
		    enic_is_notify_intr(enic, i)	||
		    !cpumask_available(enic->msix[i].affinity_mask) ||
		    cpumask_empty(enic->msix[i].affinity_mask))
			continue;
		err = irq_set_affinity_hint(enic->msix_entry[i].vector,
					    enic->msix[i].affinity_mask);
		if (err)
			netdev_warn(enic->netdev, "irq_set_affinity_hint failed, err %d\n",
				    err);
	}

	for (i = 0; i < enic->wq_count; i++) {
		int wq_intr = enic_msix_wq_intr(enic, i);

		if (cpumask_available(enic->msix[wq_intr].affinity_mask) &&
		    !cpumask_empty(enic->msix[wq_intr].affinity_mask))
			netif_set_xps_queue(enic->netdev,
					    enic->msix[wq_intr].affinity_mask,
					    i);
	}
}