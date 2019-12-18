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
struct phy {int dummy; } ;
struct imx8mq_usb_phy {int /*<<< orphan*/  vbus; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct imx8mq_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx8mq_phy_power_off(struct phy *phy)
{
	struct imx8mq_usb_phy *imx_phy = phy_get_drvdata(phy);

	clk_disable_unprepare(imx_phy->clk);
	regulator_disable(imx_phy->vbus);

	return 0;
}