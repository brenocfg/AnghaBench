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
typedef  scalar_t__ u32 ;
struct qib_devdata {struct diag_observer_list_elt* diag_observer_list; } ;
struct diag_observer_list_elt {struct diag_observer_list_elt* next; struct diag_observer* op; } ;
struct diag_observer {scalar_t__ bottom; scalar_t__ top; } ;

/* Variables and functions */

__attribute__((used)) static const struct diag_observer *diag_get_observer(struct qib_devdata *dd,
						     u32 addr)
{
	struct diag_observer_list_elt *olp;
	const struct diag_observer *op = NULL;

	olp = dd->diag_observer_list;
	while (olp) {
		op = olp->op;
		if (addr >= op->bottom && addr <= op->top)
			break;
		olp = olp->next;
	}
	if (!olp)
		op = NULL;

	return op;
}