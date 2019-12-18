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
struct TYPE_2__ {int /*<<< orphan*/  rdi; } ;
struct qib_devdata {TYPE_1__ verbs_dev; int /*<<< orphan*/  int_counter; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dbg_ibdev_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_dev_table ; 
 int /*<<< orphan*/  rvt_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void qib_free_devdata(struct qib_devdata *dd)
{
	unsigned long flags;

	xa_lock_irqsave(&qib_dev_table, flags);
	__xa_erase(&qib_dev_table, dd->unit);
	xa_unlock_irqrestore(&qib_dev_table, flags);

#ifdef CONFIG_DEBUG_FS
	qib_dbg_ibdev_exit(&dd->verbs_dev);
#endif
	free_percpu(dd->int_counter);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
}