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
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct exynos_ohci_hcd {int /*<<< orphan*/  clk; int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_ohci_phy_disable (TYPE_1__*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 struct exynos_ohci_hcd* to_exynos_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int exynos_ohci_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);

	pdev->dev.of_node = exynos_ohci->of_node;

	usb_remove_hcd(hcd);

	exynos_ohci_phy_disable(&pdev->dev);

	clk_disable_unprepare(exynos_ohci->clk);

	usb_put_hcd(hcd);

	return 0;
}