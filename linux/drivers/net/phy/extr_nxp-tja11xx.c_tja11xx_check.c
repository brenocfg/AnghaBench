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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tja11xx_check(struct phy_device *phydev, u8 reg, u16 mask, u16 set)
{
	int i, ret;

	for (i = 0; i < 200; i++) {
		ret = phy_read(phydev, reg);
		if (ret < 0)
			return ret;

		if ((ret & mask) == set)
			return 0;

		usleep_range(100, 150);
	}

	return -ETIMEDOUT;
}