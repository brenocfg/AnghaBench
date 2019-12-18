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
struct smsc911x_data {struct net_device* dev; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drv ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int smsc911x_phy_general_power_up(struct smsc911x_data *pdata)
{
	struct net_device *ndev = pdata->dev;
	struct phy_device *phy_dev = ndev->phydev;
	int rc = 0;

	if (!phy_dev)
		return rc;

	/* If the internal PHY is in General Power-Down mode, all, except the
	 * management interface, is powered-down and stays in that condition as
	 * long as Phy register bit 0.11 is HIGH.
	 *
	 * In that case, clear the bit 0.11, so the PHY powers up and we can
	 * access to the phy registers.
	 */
	rc = phy_read(phy_dev, MII_BMCR);
	if (rc < 0) {
		SMSC_WARN(pdata, drv, "Failed reading PHY control reg");
		return rc;
	}

	/* If the PHY general power-down bit is not set is not necessary to
	 * disable the general power down-mode.
	 */
	if (rc & BMCR_PDOWN) {
		rc = phy_write(phy_dev, MII_BMCR, rc & ~BMCR_PDOWN);
		if (rc < 0) {
			SMSC_WARN(pdata, drv, "Failed writing PHY control reg");
			return rc;
		}

		usleep_range(1000, 1500);
	}

	return 0;
}