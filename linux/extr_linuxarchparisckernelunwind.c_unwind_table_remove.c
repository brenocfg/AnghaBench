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
struct unwind_table {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct unwind_table*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unwind_lock ; 

void unwind_table_remove(struct unwind_table *table)
{
	unsigned long flags;

	spin_lock_irqsave(&unwind_lock, flags);
	list_del(&table->list);
	spin_unlock_irqrestore(&unwind_lock, flags);

	kfree(table);
}