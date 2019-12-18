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
struct qib_pportdata {int /*<<< orphan*/ * statusp; } ;
struct qib_devdata {int flags; scalar_t__ num_pports; int /*<<< orphan*/ * devstatusp; int /*<<< orphan*/  (* f_setextled ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;struct qib_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_IB_LINKDOWN_DISABLE ; 
 int QIB_INITTED ; 
 int QIB_PRESENT ; 
 int /*<<< orphan*/  QIB_STATUS_HWERROR ; 
 int /*<<< orphan*/  QIB_STATUS_IB_READY ; 
 int /*<<< orphan*/  qib_set_linkstate (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

void qib_disable_after_error(struct qib_devdata *dd)
{
	if (dd->flags & QIB_INITTED) {
		u32 pidx;

		dd->flags &= ~QIB_INITTED;
		if (dd->pport)
			for (pidx = 0; pidx < dd->num_pports; ++pidx) {
				struct qib_pportdata *ppd;

				ppd = dd->pport + pidx;
				if (dd->flags & QIB_PRESENT) {
					qib_set_linkstate(ppd,
						QIB_IB_LINKDOWN_DISABLE);
					dd->f_setextled(ppd, 0);
				}
				*ppd->statusp &= ~QIB_STATUS_IB_READY;
			}
	}

	/*
	 * Mark as having had an error for driver, and also
	 * for /sys and status word mapped to user programs.
	 * This marks unit as not usable, until reset.
	 */
	if (dd->devstatusp)
		*dd->devstatusp |= QIB_STATUS_HWERROR;
}