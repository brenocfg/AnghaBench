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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct qib_pportdata {int led_override; struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_1__* cspec; scalar_t__ diag_client; } ;
struct TYPE_2__ {scalar_t__ extctrl; int /*<<< orphan*/  gpio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCtrl ; 
 scalar_t__ IB_PHYSPORTSTATE_DISABLED ; 
 scalar_t__ IB_PHYSPORTSTATE_LINKUP ; 
 scalar_t__ IB_PORT_ACTIVE ; 
 scalar_t__ IB_PORT_DOWN ; 
 int /*<<< orphan*/  LEDPriPortGreenOn ; 
 int /*<<< orphan*/  LEDPriPortYellowOn ; 
 int QIB_LED_LOG ; 
 int QIB_LED_PHYS ; 
 scalar_t__ SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_extctrl ; 
 int /*<<< orphan*/  kr_ibcstatus ; 
 scalar_t__ qib_6120_iblink_state (scalar_t__) ; 
 scalar_t__ qib_6120_phys_portstate (scalar_t__) ; 
 scalar_t__ qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_6120_setup_setextled(struct qib_pportdata *ppd, u32 on)
{
	u64 extctl, val, lst, ltst;
	unsigned long flags;
	struct qib_devdata *dd = ppd->dd;

	/*
	 * The diags use the LED to indicate diag info, so we leave
	 * the external LED alone when the diags are running.
	 */
	if (dd->diag_client)
		return;

	/* Allow override of LED display for, e.g. Locating system in rack */
	if (ppd->led_override) {
		ltst = (ppd->led_override & QIB_LED_PHYS) ?
			IB_PHYSPORTSTATE_LINKUP : IB_PHYSPORTSTATE_DISABLED,
		lst = (ppd->led_override & QIB_LED_LOG) ?
			IB_PORT_ACTIVE : IB_PORT_DOWN;
	} else if (on) {
		val = qib_read_kreg64(dd, kr_ibcstatus);
		ltst = qib_6120_phys_portstate(val);
		lst = qib_6120_iblink_state(val);
	} else {
		ltst = 0;
		lst = 0;
	}

	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	extctl = dd->cspec->extctrl & ~(SYM_MASK(EXTCtrl, LEDPriPortGreenOn) |
				 SYM_MASK(EXTCtrl, LEDPriPortYellowOn));

	if (ltst == IB_PHYSPORTSTATE_LINKUP)
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortYellowOn);
	if (lst == IB_PORT_ACTIVE)
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortGreenOn);
	dd->cspec->extctrl = extctl;
	qib_write_kreg(dd, kr_extctrl, extctl);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
}