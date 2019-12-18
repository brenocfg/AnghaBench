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
 int __dwc3_gadget_start (struct dwc3*) ; 
 int /*<<< orphan*/  __dwc3_gadget_stop (struct dwc3*) ; 
 int dwc3_gadget_run_stop (struct dwc3*,int,int) ; 

int dwc3_gadget_resume(struct dwc3 *dwc)
{
	int			ret;

	if (!dwc->gadget_driver)
		return 0;

	ret = __dwc3_gadget_start(dwc);
	if (ret < 0)
		goto err0;

	ret = dwc3_gadget_run_stop(dwc, true, false);
	if (ret < 0)
		goto err1;

	return 0;

err1:
	__dwc3_gadget_stop(dwc);

err0:
	return ret;
}