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
struct qib_devdata {int /*<<< orphan*/  pioavail_lock; int /*<<< orphan*/  pport; int /*<<< orphan*/  (* f_sendctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pio_need_disarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_SENDCTRL_DISARM_BUF (unsigned int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qib_disarm_piobufs(struct qib_devdata *dd, unsigned first, unsigned cnt)
{
	unsigned long flags;
	unsigned i;
	unsigned last;

	last = first + cnt;
	spin_lock_irqsave(&dd->pioavail_lock, flags);
	for (i = first; i < last; i++) {
		__clear_bit(i, dd->pio_need_disarm);
		dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(i));
	}
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);
}