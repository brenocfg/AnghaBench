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
typedef  int /*<<< orphan*/  u32 ;
struct exynos5_usbdrd_phy {scalar_t__ reg_phy; } ;

/* Variables and functions */
 scalar_t__ EXYNOS5_DRD_PHYREG0 ; 
 int /*<<< orphan*/  PHYREG0_CR_CAP_ADDR ; 
 int /*<<< orphan*/  PHYREG0_CR_CAP_DATA ; 
 int /*<<< orphan*/  PHYREG0_CR_DATA_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYREG0_CR_WRITE ; 
 int crport_handshake (struct exynos5_usbdrd_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int crport_ctrl_write(struct exynos5_usbdrd_phy *phy_drd,
			     u32 addr, u32 data)
{
	int ret;

	/* Write Address */
	writel(PHYREG0_CR_DATA_IN(addr),
	       phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(addr),
			       PHYREG0_CR_CAP_ADDR);
	if (ret)
		return ret;

	/* Write Data */
	writel(PHYREG0_CR_DATA_IN(data),
	       phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(data),
			       PHYREG0_CR_CAP_DATA);
	if (ret)
		return ret;

	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(data),
			       PHYREG0_CR_WRITE);

	return ret;
}