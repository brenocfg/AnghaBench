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
struct qib_devdata {int /*<<< orphan*/  uctxt_lock; int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* f_hdrqempty ) (struct qib_ctxtdata*) ;} ;
struct qib_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  ppd; int /*<<< orphan*/  flag; int /*<<< orphan*/  wait; struct qib_devdata* dd; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  QIB_CTXT_WAITING_RCV ; 
 int /*<<< orphan*/  QIB_RCVCTRL_INTRAVAIL_ENB ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __poll_t qib_poll_next(struct qib_ctxtdata *rcd,
				  struct file *fp,
				  struct poll_table_struct *pt)
{
	struct qib_devdata *dd = rcd->dd;
	__poll_t pollflag;

	poll_wait(fp, &rcd->wait, pt);

	spin_lock_irq(&dd->uctxt_lock);
	if (dd->f_hdrqempty(rcd)) {
		set_bit(QIB_CTXT_WAITING_RCV, &rcd->flag);
		dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_INTRAVAIL_ENB, rcd->ctxt);
		pollflag = 0;
	} else
		pollflag = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&dd->uctxt_lock);

	return pollflag;
}