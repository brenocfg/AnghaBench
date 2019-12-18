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
struct ionic_deferred_work {int /*<<< orphan*/  list; } ;
struct ionic_deferred {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_lif_deferred_enqueue(struct ionic_deferred *def,
				       struct ionic_deferred_work *work)
{
	spin_lock_bh(&def->lock);
	list_add_tail(&work->list, &def->list);
	spin_unlock_bh(&def->lock);
	schedule_work(&def->work);
}