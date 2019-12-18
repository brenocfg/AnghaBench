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
struct ena_irq {int /*<<< orphan*/  data; int /*<<< orphan*/  vector; } ;
struct ena_adapter {struct ena_irq* irq_tbl; } ;

/* Variables and functions */
 size_t ENA_MGMNT_IRQ_IDX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_free_mgmnt_irq(struct ena_adapter *adapter)
{
	struct ena_irq *irq;

	irq = &adapter->irq_tbl[ENA_MGMNT_IRQ_IDX];
	synchronize_irq(irq->vector);
	irq_set_affinity_hint(irq->vector, NULL);
	free_irq(irq->vector, irq->data);
}