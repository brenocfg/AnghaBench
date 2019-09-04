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
struct qib_ctxtdata {scalar_t__ poll_type; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 scalar_t__ QIB_POLL_TYPE_ANYRCV ; 
 scalar_t__ QIB_POLL_TYPE_URGENT ; 
 struct qib_ctxtdata* ctxt_fp (struct file*) ; 
 int /*<<< orphan*/  qib_poll_next (struct qib_ctxtdata*,struct file*,struct poll_table_struct*) ; 
 int /*<<< orphan*/  qib_poll_urgent (struct qib_ctxtdata*,struct file*,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t qib_poll(struct file *fp, struct poll_table_struct *pt)
{
	struct qib_ctxtdata *rcd;
	__poll_t pollflag;

	rcd = ctxt_fp(fp);
	if (!rcd)
		pollflag = EPOLLERR;
	else if (rcd->poll_type == QIB_POLL_TYPE_URGENT)
		pollflag = qib_poll_urgent(rcd, fp, pt);
	else  if (rcd->poll_type == QIB_POLL_TYPE_ANYRCV)
		pollflag = qib_poll_next(rcd, fp, pt);
	else /* invalid */
		pollflag = EPOLLERR;

	return pollflag;
}