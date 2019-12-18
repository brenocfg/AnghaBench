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
 int /*<<< orphan*/  ADIN1300_GE_SOFT_RESET ; 
 int /*<<< orphan*/  ADIN1300_GE_SOFT_RESET_REG ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_set_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adin_soft_reset(struct phy_device *phydev)
{
	int rc;

	/* The reset bit is self-clearing, set it and wait */
	rc = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
			      ADIN1300_GE_SOFT_RESET_REG,
			      ADIN1300_GE_SOFT_RESET);
	if (rc < 0)
		return rc;

	msleep(10);

	/* If we get a read error something may be wrong */
	rc = phy_read_mmd(phydev, MDIO_MMD_VEND1,
			  ADIN1300_GE_SOFT_RESET_REG);

	return rc < 0 ? rc : 0;
}