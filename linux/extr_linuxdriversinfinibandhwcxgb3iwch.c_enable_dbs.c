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
struct iwch_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  qpidr; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_qp_db ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_dbs(struct iwch_dev *rnicp, int ring_db)
{
	spin_lock_irq(&rnicp->lock);
	idr_for_each(&rnicp->qpidr, enable_qp_db,
		     (void *)(unsigned long)ring_db);
	spin_unlock_irq(&rnicp->lock);
}