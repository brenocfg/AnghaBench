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
struct xhci_hcd_histb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;

/* Variables and functions */
 struct xhci_hcd_histb* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xhci_hcd_histb *hcd_to_histb(struct usb_hcd *hcd)
{
	return dev_get_drvdata(hcd->self.controller);
}