#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int phy_id; } ;
struct ioc3_private {TYPE_1__ mii; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int ioc3_mdio_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioc3_mii_init(struct ioc3_private *ip)
{
	int ioc3_phy_workaround = 1;
	int i, found = 0, res = 0;
	u16 word;

	for (i = 0; i < 32; i++) {
		word = ioc3_mdio_read(ip->dev, i, MII_PHYSID1);

		if (word != 0xffff && word != 0x0000) {
			found = 1;
			break;			/* Found a PHY		*/
		}
	}

	if (!found) {
		if (ioc3_phy_workaround) {
			i = 31;
		} else {
			ip->mii.phy_id = -1;
			res = -ENODEV;
			goto out;
		}
	}

	ip->mii.phy_id = i;

out:
	return res;
}