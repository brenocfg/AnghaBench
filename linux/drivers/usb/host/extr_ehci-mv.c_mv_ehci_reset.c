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
struct TYPE_2__ {struct device* controller; } ;
struct usb_hcd {int has_tt; TYPE_1__ self; } ;
struct ehci_hcd_mv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int ehci_setup (struct usb_hcd*) ; 
 struct ehci_hcd_mv* hcd_to_ehci_hcd_mv (struct usb_hcd*) ; 

__attribute__((used)) static int mv_ehci_reset(struct usb_hcd *hcd)
{
	struct device *dev = hcd->self.controller;
	struct ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);
	int retval;

	if (ehci_mv == NULL) {
		dev_err(dev, "Can not find private ehci data\n");
		return -ENODEV;
	}

	hcd->has_tt = 1;

	retval = ehci_setup(hcd);
	if (retval)
		dev_err(dev, "ehci_setup failed %d\n", retval);

	return retval;
}