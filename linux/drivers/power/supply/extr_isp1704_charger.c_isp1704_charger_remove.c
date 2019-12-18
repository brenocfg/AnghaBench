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
struct isp1704_charger {int /*<<< orphan*/  psy; int /*<<< orphan*/  nb; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp1704_charger_set_power (struct isp1704_charger*,int /*<<< orphan*/ ) ; 
 struct isp1704_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp1704_charger_remove(struct platform_device *pdev)
{
	struct isp1704_charger *isp = platform_get_drvdata(pdev);

	usb_unregister_notifier(isp->phy, &isp->nb);
	power_supply_unregister(isp->psy);
	isp1704_charger_set_power(isp, 0);

	return 0;
}