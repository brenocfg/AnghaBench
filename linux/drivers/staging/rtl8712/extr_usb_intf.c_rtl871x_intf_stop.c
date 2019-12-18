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
struct TYPE_2__ {int /*<<< orphan*/  (* inirp_deinit ) (struct _adapter*) ;} ;
struct _adapter {TYPE_1__ dvobjpriv; int /*<<< orphan*/  surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_usb_write_port_cancel (struct _adapter*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*) ; 

void rtl871x_intf_stop(struct _adapter *padapter)
{
	/*disable_hw_interrupt*/
	if (!padapter->surprise_removed) {
		/*device still exists, so driver can do i/o operation
		 * TODO:
		 */
	}

	/* cancel in irp */
	if (padapter->dvobjpriv.inirp_deinit)
		padapter->dvobjpriv.inirp_deinit(padapter);
	/* cancel out irp */
	r8712_usb_write_port_cancel(padapter);
	/* TODO:cancel other irps */
}