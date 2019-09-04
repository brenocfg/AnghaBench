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
typedef  int /*<<< orphan*/  u32 ;
struct c4iw_id_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  table; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void c4iw_id_free(struct c4iw_id_table *alloc, u32 obj)
{
	unsigned long flags;

	obj -= alloc->start;

	spin_lock_irqsave(&alloc->lock, flags);
	clear_bit(obj, alloc->table);
	spin_unlock_irqrestore(&alloc->lock, flags);
}