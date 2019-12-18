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
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_write (struct mii_phy*,int,int) ; 

__attribute__((used)) static int ar8035_init(struct mii_phy *phy)
{
	phy_write(phy, 0x1d, 0x5); /* Address debug register 5 */
	phy_write(phy, 0x1e, 0x2d47); /* Value copied from u-boot */
	phy_write(phy, 0x1d, 0xb);    /* Address hib ctrl */
	phy_write(phy, 0x1e, 0xbc20); /* Value copied from u-boot */

	return 0;
}