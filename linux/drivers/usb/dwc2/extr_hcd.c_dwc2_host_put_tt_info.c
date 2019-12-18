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
struct dwc2_tt {int refcount; TYPE_1__* usb_tt; } ;
struct dwc2_hsotg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct dwc2_tt*) ; 

void dwc2_host_put_tt_info(struct dwc2_hsotg *hsotg, struct dwc2_tt *dwc_tt)
{
	/* Model kfree and make put of NULL a no-op */
	if (!dwc_tt)
		return;

	WARN_ON(dwc_tt->refcount < 1);

	dwc_tt->refcount--;
	if (!dwc_tt->refcount) {
		dwc_tt->usb_tt->hcpriv = NULL;
		kfree(dwc_tt);
	}
}