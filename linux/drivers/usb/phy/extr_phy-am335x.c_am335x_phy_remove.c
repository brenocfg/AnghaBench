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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy; } ;
struct am335x_phy {TYPE_1__ usb_phy_gen; } ;

/* Variables and functions */
 struct am335x_phy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int am335x_phy_remove(struct platform_device *pdev)
{
	struct am335x_phy *am_phy = platform_get_drvdata(pdev);

	usb_remove_phy(&am_phy->usb_phy_gen.phy);
	return 0;
}