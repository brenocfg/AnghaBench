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
struct pvrdma_uar_map {int index; } ;
struct pvrdma_id_table {int max; int top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  last; int /*<<< orphan*/  table; } ;
struct TYPE_2__ {struct pvrdma_id_table tbl; } ;
struct pvrdma_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pvrdma_uar_free(struct pvrdma_dev *dev, struct pvrdma_uar_map *uar)
{
	struct pvrdma_id_table *tbl = &dev->uar_table.tbl;
	unsigned long flags;
	u32 obj;

	obj = uar->index & (tbl->max - 1);
	spin_lock_irqsave(&tbl->lock, flags);
	clear_bit(obj, tbl->table);
	tbl->last = min(tbl->last, obj);
	tbl->top = (tbl->top + tbl->max) & tbl->mask;
	spin_unlock_irqrestore(&tbl->lock, flags);
}