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
struct usb_hcd {TYPE_1__* driver; int /*<<< orphan*/  flags; } ;
struct sa1111_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 struct usb_hcd* sa1111_get_drvdata (struct sa1111_dev*) ; 
 int /*<<< orphan*/  sa1111_stop_hc (struct sa1111_dev*) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sa1111_dev* to_sa1111_device (struct device*) ; 

__attribute__((used)) static void ohci_hcd_sa1111_shutdown(struct device *_dev)
{
	struct sa1111_dev *dev = to_sa1111_device(_dev);
	struct usb_hcd *hcd = sa1111_get_drvdata(dev);

	if (test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags)) {
		hcd->driver->shutdown(hcd);
		sa1111_stop_hc(dev);
	}
}