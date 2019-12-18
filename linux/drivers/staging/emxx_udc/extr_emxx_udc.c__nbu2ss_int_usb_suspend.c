#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nbu2ss_udc {int usb_suspended; TYPE_1__* p_regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* suspend ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  USB_CONTROL; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbus_gpio ; 

__attribute__((used)) static inline void _nbu2ss_int_usb_suspend(struct nbu2ss_udc *udc)
{
	u32	reg_dt;

	if (udc->usb_suspended == 0) {
		reg_dt = gpiod_get_value(vbus_gpio);

		if (reg_dt == 0)
			return;

		udc->usb_suspended = 1;
		if (udc->driver && udc->driver->suspend) {
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		}

		_nbu2ss_bitset(&udc->p_regs->USB_CONTROL, SUSPEND);
	}
}