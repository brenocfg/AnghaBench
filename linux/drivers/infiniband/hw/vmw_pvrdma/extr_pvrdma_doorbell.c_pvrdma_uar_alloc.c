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
typedef  int u32 ;
struct pvrdma_uar_map {int index; int pfn; } ;
struct pvrdma_id_table {int max; int top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; int /*<<< orphan*/  last; } ;
struct TYPE_2__ {struct pvrdma_id_table tbl; } ;
struct pvrdma_dev {int /*<<< orphan*/  pdev; TYPE_1__ uar_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PVRDMA_PCI_RESOURCE_UAR ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pvrdma_uar_alloc(struct pvrdma_dev *dev, struct pvrdma_uar_map *uar)
{
	struct pvrdma_id_table *tbl;
	unsigned long flags;
	u32 obj;

	tbl = &dev->uar_table.tbl;

	spin_lock_irqsave(&tbl->lock, flags);
	obj = find_next_zero_bit(tbl->table, tbl->max, tbl->last);
	if (obj >= tbl->max) {
		tbl->top = (tbl->top + tbl->max) & tbl->mask;
		obj = find_first_zero_bit(tbl->table, tbl->max);
	}

	if (obj >= tbl->max) {
		spin_unlock_irqrestore(&tbl->lock, flags);
		return -ENOMEM;
	}

	set_bit(obj, tbl->table);
	obj |= tbl->top;

	spin_unlock_irqrestore(&tbl->lock, flags);

	uar->index = obj;
	uar->pfn = (pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_UAR) >>
		    PAGE_SHIFT) + uar->index;

	return 0;
}