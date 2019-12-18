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
struct usb_hcd {int dummy; } ;
struct pxa27x_ohci {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa27x_ohci_set_vbus_power (struct pxa27x_ohci*,unsigned int,int) ; 
 int /*<<< orphan*/  pxa27x_stop_hc (struct pxa27x_ohci*,int /*<<< orphan*/ *) ; 
 struct pxa27x_ohci* to_pxa27x_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_pxa27x_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	unsigned int i;

	usb_remove_hcd(hcd);
	pxa27x_stop_hc(pxa_ohci, &pdev->dev);

	for (i = 0; i < 3; ++i)
		pxa27x_ohci_set_vbus_power(pxa_ohci, i, false);

	usb_put_hcd(hcd);
	return 0;
}