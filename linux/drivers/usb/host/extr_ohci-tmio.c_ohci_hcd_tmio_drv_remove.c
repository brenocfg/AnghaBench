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
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct tmio_hcd {int /*<<< orphan*/  ccr; } ;
struct platform_device {int dummy; } ;
struct mfd_cell {int /*<<< orphan*/  (* disable ) (struct platform_device*) ;} ;

/* Variables and functions */
 struct tmio_hcd* hcd_to_tmio (struct usb_hcd*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct mfd_cell* mfd_get_cell (struct platform_device*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_stop_hc (struct platform_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_tmio_drv_remove(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct tmio_hcd *tmio = hcd_to_tmio(hcd);
	const struct mfd_cell *cell = mfd_get_cell(dev);

	usb_remove_hcd(hcd);
	tmio_stop_hc(dev);
	if (cell->disable)
		cell->disable(dev);
	iounmap(hcd->regs);
	iounmap(tmio->ccr);
	usb_put_hcd(hcd);

	return 0;
}