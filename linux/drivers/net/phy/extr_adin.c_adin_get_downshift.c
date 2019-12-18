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
 int /*<<< orphan*/  ADIN1300_DOWNSPEEDS_EN ; 
 int /*<<< orphan*/  ADIN1300_DOWNSPEED_RETRIES_MSK ; 
 int /*<<< orphan*/  ADIN1300_PHY_CTRL2 ; 
 int /*<<< orphan*/  ADIN1300_PHY_CTRL3 ; 
 int DOWNSHIFT_DEV_DISABLE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adin_get_downshift(struct phy_device *phydev, u8 *data)
{
	int val, cnt, enable;

	val = phy_read(phydev, ADIN1300_PHY_CTRL2);
	if (val < 0)
		return val;

	cnt = phy_read(phydev, ADIN1300_PHY_CTRL3);
	if (cnt < 0)
		return cnt;

	enable = FIELD_GET(ADIN1300_DOWNSPEEDS_EN, val);
	cnt = FIELD_GET(ADIN1300_DOWNSPEED_RETRIES_MSK, cnt);

	*data = (enable && cnt) ? cnt : DOWNSHIFT_DEV_DISABLE;

	return 0;
}