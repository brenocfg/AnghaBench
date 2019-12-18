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
struct qib_devdata {int /*<<< orphan*/  qib_diag_trans_lock; struct diag_observer_list_elt* diag_observer_list; } ;
struct diag_observer_list_elt {struct diag_observer_list_elt* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (struct diag_observer_list_elt*) ; 

__attribute__((used)) static void qib_unregister_observers(struct qib_devdata *dd)
{
	struct diag_observer_list_elt *olp;
	unsigned long flags;

	spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
	olp = dd->diag_observer_list;
	while (olp) {
		/* Pop one observer, let go of lock */
		dd->diag_observer_list = olp->next;
		spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
		vfree(olp);
		/* try again. */
		spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
		olp = dd->diag_observer_list;
	}
	spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
}