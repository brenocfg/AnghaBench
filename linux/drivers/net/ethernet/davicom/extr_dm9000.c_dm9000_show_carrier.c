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
struct net_device {int /*<<< orphan*/  name; } ;
struct mii_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_id; int /*<<< orphan*/  dev; } ;
struct board_info {int /*<<< orphan*/  dev; struct mii_if_info mii; struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_NCR ; 
 int /*<<< orphan*/  MII_LPA ; 
 unsigned int NCR_FDX ; 
 unsigned int NSR_SPEED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 unsigned int dm9000_read_locked (struct board_info*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm9000_show_carrier(struct board_info *db,
				unsigned carrier, unsigned nsr)
{
	int lpa;
	struct net_device *ndev = db->ndev;
	struct mii_if_info *mii = &db->mii;
	unsigned ncr = dm9000_read_locked(db, DM9000_NCR);

	if (carrier) {
		lpa = mii->mdio_read(mii->dev, mii->phy_id, MII_LPA);
		dev_info(db->dev,
			 "%s: link up, %dMbps, %s-duplex, lpa 0x%04X\n",
			 ndev->name, (nsr & NSR_SPEED) ? 10 : 100,
			 (ncr & NCR_FDX) ? "full" : "half", lpa);
	} else {
		dev_info(db->dev, "%s: link down\n", ndev->name);
	}
}