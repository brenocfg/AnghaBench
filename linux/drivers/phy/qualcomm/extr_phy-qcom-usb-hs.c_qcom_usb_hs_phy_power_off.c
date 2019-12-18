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
struct qcom_usb_hs_phy {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  sleep_clk; int /*<<< orphan*/  v1p8; int /*<<< orphan*/  v3p3; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_usb_hs_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_usb_hs_phy_power_off(struct phy *phy)
{
	struct qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);

	regulator_disable(uphy->v3p3);
	regulator_disable(uphy->v1p8);
	clk_disable_unprepare(uphy->sleep_clk);
	clk_disable_unprepare(uphy->ref_clk);

	return 0;
}