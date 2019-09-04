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
struct iser_fr_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct iser_fr_desc {int /*<<< orphan*/  list; } ;
struct ib_conn {struct iser_fr_pool fr_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
iser_reg_desc_put_fr(struct ib_conn *ib_conn,
		     struct iser_fr_desc *desc)
{
	struct iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	unsigned long flags;

	spin_lock_irqsave(&fr_pool->lock, flags);
	list_add(&desc->list, &fr_pool->list);
	spin_unlock_irqrestore(&fr_pool->lock, flags);
}