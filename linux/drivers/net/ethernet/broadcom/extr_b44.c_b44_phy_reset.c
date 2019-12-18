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
typedef  int u32 ;
struct b44 {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int B44_FLAG_EXTERNAL_PHY ; 
 int BMCR_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int b44_readphy (struct b44*,int /*<<< orphan*/ ,int*) ; 
 int b44_writephy (struct b44*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int b44_phy_reset(struct b44 *bp)
{
	u32 val;
	int err;

	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		return 0;
	err = b44_writephy(bp, MII_BMCR, BMCR_RESET);
	if (err)
		return err;
	udelay(100);
	err = b44_readphy(bp, MII_BMCR, &val);
	if (!err) {
		if (val & BMCR_RESET) {
			netdev_err(bp->dev, "PHY Reset would not complete\n");
			err = -ENODEV;
		}
	}

	return err;
}