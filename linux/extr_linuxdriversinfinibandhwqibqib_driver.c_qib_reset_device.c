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
struct qib_pportdata {int /*<<< orphan*/  led_override; int /*<<< orphan*/  led_override_timer_active; int /*<<< orphan*/  led_override_timer; } ;
struct qib_devdata {int flags; int first_user_ctxt; int cfgctxts; int num_pports; int (* f_reset ) (struct qib_devdata*) ;int /*<<< orphan*/  pcidev; int /*<<< orphan*/  (* f_setextled ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;struct qib_pportdata* pport; int /*<<< orphan*/  uctxt_lock; TYPE_1__** rcd; int /*<<< orphan*/  kregbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  LED_OVER_BOTH_OFF ; 
 int QIB_HAS_SEND_DMA ; 
 int QIB_PRESENT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int,int) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int) ; 
 int qib_init (struct qib_devdata*,int) ; 
 struct qib_devdata* qib_lookup (int) ; 
 int /*<<< orphan*/  qib_teardown_sdma (struct qib_pportdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int stub2 (struct qib_devdata*) ; 

int qib_reset_device(int unit)
{
	int ret, i;
	struct qib_devdata *dd = qib_lookup(unit);
	struct qib_pportdata *ppd;
	unsigned long flags;
	int pidx;

	if (!dd) {
		ret = -ENODEV;
		goto bail;
	}

	qib_devinfo(dd->pcidev, "Reset on unit %u requested\n", unit);

	if (!dd->kregbase || !(dd->flags & QIB_PRESENT)) {
		qib_devinfo(dd->pcidev,
			"Invalid unit number %u or not initialized or not present\n",
			unit);
		ret = -ENXIO;
		goto bail;
	}

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	if (dd->rcd)
		for (i = dd->first_user_ctxt; i < dd->cfgctxts; i++) {
			if (!dd->rcd[i] || !dd->rcd[i]->cnt)
				continue;
			spin_unlock_irqrestore(&dd->uctxt_lock, flags);
			ret = -EBUSY;
			goto bail;
		}
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (atomic_read(&ppd->led_override_timer_active)) {
			/* Need to stop LED timer, _then_ shut off LEDs */
			del_timer_sync(&ppd->led_override_timer);
			atomic_set(&ppd->led_override_timer_active, 0);
		}

		/* Shut off LEDs after we are sure timer is not running */
		ppd->led_override = LED_OVER_BOTH_OFF;
		dd->f_setextled(ppd, 0);
		if (dd->flags & QIB_HAS_SEND_DMA)
			qib_teardown_sdma(ppd);
	}

	ret = dd->f_reset(dd);
	if (ret == 1)
		ret = qib_init(dd, 1);
	else
		ret = -EAGAIN;
	if (ret)
		qib_dev_err(dd,
			"Reinitialize unit %u after reset failed with %d\n",
			unit, ret);
	else
		qib_devinfo(dd->pcidev,
			"Reinitialized unit %u after resetting\n",
			unit);

bail:
	return ret;
}