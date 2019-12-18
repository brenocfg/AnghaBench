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
struct vmd_irq {int enabled; int /*<<< orphan*/  node; } ;
struct irq_data {TYPE_1__* chip; struct vmd_irq* chip_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_mask ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void vmd_irq_disable(struct irq_data *data)
{
	struct vmd_irq *vmdirq = data->chip_data;
	unsigned long flags;

	data->chip->irq_mask(data);

	raw_spin_lock_irqsave(&list_lock, flags);
	if (vmdirq->enabled) {
		list_del_rcu(&vmdirq->node);
		vmdirq->enabled = false;
	}
	raw_spin_unlock_irqrestore(&list_lock, flags);
}