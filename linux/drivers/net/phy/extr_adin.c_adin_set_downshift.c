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
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIN1300_DOWNSPEEDS_EN ; 
 int ADIN1300_DOWNSPEED_RETRIES_MSK ; 
 int ADIN1300_LINKING_EN ; 
 int /*<<< orphan*/  ADIN1300_PHY_CTRL2 ; 
 int /*<<< orphan*/  ADIN1300_PHY_CTRL3 ; 
 int DOWNSHIFT_DEV_DISABLE ; 
 int E2BIG ; 
 int FIELD_PREP (int,int) ; 
 int phy_clear_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 
 int phy_set_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adin_set_downshift(struct phy_device *phydev, u8 cnt)
{
	u16 val;
	int rc;

	if (cnt == DOWNSHIFT_DEV_DISABLE)
		return phy_clear_bits(phydev, ADIN1300_PHY_CTRL2,
				      ADIN1300_DOWNSPEEDS_EN);

	if (cnt > 7)
		return -E2BIG;

	val = FIELD_PREP(ADIN1300_DOWNSPEED_RETRIES_MSK, cnt);
	val |= ADIN1300_LINKING_EN;

	rc = phy_modify(phydev, ADIN1300_PHY_CTRL3,
			ADIN1300_LINKING_EN | ADIN1300_DOWNSPEED_RETRIES_MSK,
			val);
	if (rc < 0)
		return rc;

	return phy_set_bits(phydev, ADIN1300_PHY_CTRL2,
			    ADIN1300_DOWNSPEEDS_EN);
}