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
struct stm32_usbphyc_phy {int /*<<< orphan*/  supplies; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_SUPPLIES ; 
 struct stm32_usbphyc_phy* phy_get_drvdata (struct phy*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_usbphyc_phy_power_on(struct phy *phy)
{
	struct stm32_usbphyc_phy *usbphyc_phy = phy_get_drvdata(phy);

	return regulator_bulk_enable(NUM_SUPPLIES, usbphyc_phy->supplies);
}