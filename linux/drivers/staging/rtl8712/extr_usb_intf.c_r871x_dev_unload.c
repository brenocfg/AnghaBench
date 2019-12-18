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
struct _adapter {int bup; int driver_stopped; int hw_init_completed; int /*<<< orphan*/  (* dvobj_deinit ) (struct _adapter*) ;int /*<<< orphan*/  surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_stop_drv_threads (struct _adapter*) ; 
 int /*<<< orphan*/  rtl8712_hal_deinit (struct _adapter*) ; 
 int /*<<< orphan*/  rtl871x_intf_stop (struct _adapter*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*) ; 

void r871x_dev_unload(struct _adapter *padapter)
{
	if (padapter->bup) {
		/*s1.*/
		padapter->driver_stopped = true;

		/*s3.*/
		rtl871x_intf_stop(padapter);

		/*s4.*/
		r8712_stop_drv_threads(padapter);

		/*s5.*/
		if (!padapter->surprise_removed) {
			padapter->hw_init_completed = false;
			rtl8712_hal_deinit(padapter);
		}

		/*s6.*/
		if (padapter->dvobj_deinit)
			padapter->dvobj_deinit(padapter);
		padapter->bup = false;
	}
}