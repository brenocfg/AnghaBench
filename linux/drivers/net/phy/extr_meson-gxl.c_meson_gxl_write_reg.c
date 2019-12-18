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
typedef  int uint16_t ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TSTCNTL ; 
 int /*<<< orphan*/  TSTCNTL_REG_BANK_SEL ; 
 int TSTCNTL_TEST_MODE ; 
 int TSTCNTL_WRITE ; 
 int /*<<< orphan*/  TSTCNTL_WRITE_ADDRESS ; 
 int /*<<< orphan*/  TSTWRITE ; 
 int /*<<< orphan*/  meson_gxl_close_banks (struct phy_device*) ; 
 int meson_gxl_open_banks (struct phy_device*) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_gxl_write_reg(struct phy_device *phydev,
			       unsigned int bank, unsigned int reg,
			       uint16_t value)
{
	int ret;

	ret = meson_gxl_open_banks(phydev);
	if (ret)
		goto out;

	ret = phy_write(phydev, TSTWRITE, value);
	if (ret)
		goto out;

	ret = phy_write(phydev, TSTCNTL, TSTCNTL_WRITE |
			FIELD_PREP(TSTCNTL_REG_BANK_SEL, bank) |
			TSTCNTL_TEST_MODE |
			FIELD_PREP(TSTCNTL_WRITE_ADDRESS, reg));

out:
	/* Close the bank access on our way out */
	meson_gxl_close_banks(phydev);
	return ret;
}