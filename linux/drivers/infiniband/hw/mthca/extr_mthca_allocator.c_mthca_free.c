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
typedef  int u32 ;
struct mthca_alloc {int max; int top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  last; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mthca_free(struct mthca_alloc *alloc, u32 obj)
{
	unsigned long flags;

	obj &= alloc->max - 1;

	spin_lock_irqsave(&alloc->lock, flags);

	clear_bit(obj, alloc->table);
	alloc->last = min(alloc->last, obj);
	alloc->top = (alloc->top + alloc->max) & alloc->mask;

	spin_unlock_irqrestore(&alloc->lock, flags);
}