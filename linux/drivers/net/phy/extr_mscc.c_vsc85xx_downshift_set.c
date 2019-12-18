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
typedef  int u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOWNSHIFT_CNTL_MASK ; 
 int DOWNSHIFT_CNTL_POS ; 
 int DOWNSHIFT_COUNT_MAX ; 
 int DOWNSHIFT_DEV_DEFAULT_COUNT ; 
 int DOWNSHIFT_EN ; 
 int ERANGE ; 
 int /*<<< orphan*/  MSCC_PHY_ACTIPHY_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED ; 
 int phy_modify_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

__attribute__((used)) static int vsc85xx_downshift_set(struct phy_device *phydev, u8 count)
{
	if (count == DOWNSHIFT_DEV_DEFAULT_COUNT) {
		/* Default downshift count 3 (i.e. Bit3:2 = 0b01) */
		count = ((1 << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	} else if (count > DOWNSHIFT_COUNT_MAX || count == 1) {
		phydev_err(phydev, "Downshift count should be 2,3,4 or 5\n");
		return -ERANGE;
	} else if (count) {
		/* Downshift count is either 2,3,4 or 5 */
		count = (((count - 2) << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	}

	return phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
				MSCC_PHY_ACTIPHY_CNTL, DOWNSHIFT_CNTL_MASK,
				count);
}