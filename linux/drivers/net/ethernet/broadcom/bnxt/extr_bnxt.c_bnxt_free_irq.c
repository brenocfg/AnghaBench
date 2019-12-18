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
struct bnxt_irq {scalar_t__ requested; int /*<<< orphan*/  vector; scalar_t__ have_cpumask; int /*<<< orphan*/  cpu_mask; } ;
struct bnxt {int cp_nr_rings; int /*<<< orphan*/ * bnapi; struct bnxt_irq* irq_tbl; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int bnxt_cp_num_to_irq_num (struct bnxt*,int) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_irq(struct bnxt *bp)
{
	struct bnxt_irq *irq;
	int i;

#ifdef CONFIG_RFS_ACCEL
	free_irq_cpu_rmap(bp->dev->rx_cpu_rmap);
	bp->dev->rx_cpu_rmap = NULL;
#endif
	if (!bp->irq_tbl || !bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		int map_idx = bnxt_cp_num_to_irq_num(bp, i);

		irq = &bp->irq_tbl[map_idx];
		if (irq->requested) {
			if (irq->have_cpumask) {
				irq_set_affinity_hint(irq->vector, NULL);
				free_cpumask_var(irq->cpu_mask);
				irq->have_cpumask = 0;
			}
			free_irq(irq->vector, bp->bnapi[i]);
		}

		irq->requested = 0;
	}
}