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
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mii_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mii_reset(struct niu *np)
{
	int limit, err;

	err = mii_write(np, np->phy_addr, MII_BMCR, BMCR_RESET);
	if (err)
		return err;

	limit = 1000;
	while (--limit >= 0) {
		udelay(500);
		err = mii_read(np, np->phy_addr, MII_BMCR);
		if (err < 0)
			return err;
		if (!(err & BMCR_RESET))
			break;
	}
	if (limit < 0) {
		netdev_err(np->dev, "Port %u MII would not reset, bmcr[%04x]\n",
			   np->port, err);
		return -ENODEV;
	}

	return 0;
}