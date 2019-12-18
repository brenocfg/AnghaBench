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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct atmel_ehci_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_start_clock (struct atmel_ehci_priv*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct atmel_ehci_priv* hcd_to_atmel_ehci_priv (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void atmel_start_ehci(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct atmel_ehci_priv *atmel_ehci = hcd_to_atmel_ehci_priv(hcd);

	dev_dbg(&pdev->dev, "start\n");
	atmel_start_clock(atmel_ehci);
}