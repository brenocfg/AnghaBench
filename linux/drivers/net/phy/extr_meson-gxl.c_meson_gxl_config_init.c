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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_BIST ; 
 int /*<<< orphan*/  FR_PLL_CONTROL ; 
 int /*<<< orphan*/  FR_PLL_DIV0 ; 
 int /*<<< orphan*/  FR_PLL_DIV1 ; 
 int meson_gxl_write_reg (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_gxl_config_init(struct phy_device *phydev)
{
	int ret;

	/* Enable fractional PLL */
	ret = meson_gxl_write_reg(phydev, BANK_BIST, FR_PLL_CONTROL, 0x5);
	if (ret)
		return ret;

	/* Program fraction FR_PLL_DIV1 */
	ret = meson_gxl_write_reg(phydev, BANK_BIST, FR_PLL_DIV1, 0x029a);
	if (ret)
		return ret;

	/* Program fraction FR_PLL_DIV1 */
	ret = meson_gxl_write_reg(phydev, BANK_BIST, FR_PLL_DIV0, 0xaaaa);
	if (ret)
		return ret;

	return 0;
}