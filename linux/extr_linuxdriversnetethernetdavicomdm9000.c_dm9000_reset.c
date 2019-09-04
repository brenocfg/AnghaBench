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
struct board_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_NCR ; 
 int NCR_MAC_LBK ; 
 int NCR_RST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ior (struct board_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
dm9000_reset(struct board_info *db)
{
	dev_dbg(db->dev, "resetting device\n");

	/* Reset DM9000, see DM9000 Application Notes V1.22 Jun 11, 2004 page 29
	 * The essential point is that we have to do a double reset, and the
	 * instruction is to set LBK into MAC internal loopback mode.
	 */
	iow(db, DM9000_NCR, NCR_RST | NCR_MAC_LBK);
	udelay(100); /* Application note says at least 20 us */
	if (ior(db, DM9000_NCR) & 1)
		dev_err(db->dev, "dm9000 did not respond to first reset\n");

	iow(db, DM9000_NCR, 0);
	iow(db, DM9000_NCR, NCR_RST | NCR_MAC_LBK);
	udelay(100);
	if (ior(db, DM9000_NCR) & 1)
		dev_err(db->dev, "dm9000 did not respond to second reset\n");
}