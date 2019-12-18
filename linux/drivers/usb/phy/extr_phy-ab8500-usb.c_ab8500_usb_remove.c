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
struct platform_device {int dummy; } ;
struct ab8500_usb {scalar_t__ mode; int /*<<< orphan*/  phy; int /*<<< orphan*/  phy_dis_work; } ;

/* Variables and functions */
 scalar_t__ USB_HOST ; 
 scalar_t__ USB_PERIPHERAL ; 
 int /*<<< orphan*/  ab8500_usb_host_phy_dis (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_peri_phy_dis (struct ab8500_usb*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct ab8500_usb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab8500_usb_remove(struct platform_device *pdev)
{
	struct ab8500_usb *ab = platform_get_drvdata(pdev);

	cancel_work_sync(&ab->phy_dis_work);

	usb_remove_phy(&ab->phy);

	if (ab->mode == USB_HOST)
		ab8500_usb_host_phy_dis(ab);
	else if (ab->mode == USB_PERIPHERAL)
		ab8500_usb_peri_phy_dis(ab);

	return 0;
}