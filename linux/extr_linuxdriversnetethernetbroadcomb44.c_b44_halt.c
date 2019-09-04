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
struct b44 {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_CHIP_RESET_FULL ; 
 int /*<<< orphan*/  B44_CHIP_RESET_PARTIAL ; 
 int B44_FLAG_EXTERNAL_PHY ; 
 int /*<<< orphan*/  B44_MAC_CTRL ; 
 int /*<<< orphan*/  MAC_CTRL_PHY_PDOWN ; 
 int /*<<< orphan*/  b44_chip_reset (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_disable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_phy_reset (struct b44*) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b44_halt(struct b44 *bp)
{
	b44_disable_ints(bp);
	/* reset PHY */
	b44_phy_reset(bp);
	/* power down PHY */
	netdev_info(bp->dev, "powering down PHY\n");
	bw32(bp, B44_MAC_CTRL, MAC_CTRL_PHY_PDOWN);
	/* now reset the chip, but without enabling the MAC&PHY
	 * part of it. This has to be done _after_ we shut down the PHY */
	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		b44_chip_reset(bp, B44_CHIP_RESET_FULL);
	else
		b44_chip_reset(bp, B44_CHIP_RESET_PARTIAL);
}