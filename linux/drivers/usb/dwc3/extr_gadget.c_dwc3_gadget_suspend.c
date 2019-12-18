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
struct dwc3 {int /*<<< orphan*/  gadget_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dwc3_gadget_stop (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_disconnect_gadget (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_run_stop (struct dwc3*,int,int) ; 

int dwc3_gadget_suspend(struct dwc3 *dwc)
{
	if (!dwc->gadget_driver)
		return 0;

	dwc3_gadget_run_stop(dwc, false, false);
	dwc3_disconnect_gadget(dwc);
	__dwc3_gadget_stop(dwc);

	return 0;
}