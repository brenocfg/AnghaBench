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
struct phy_device {int dummy; } ;
struct fixed_phy_status {int link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct bgmac {int /*<<< orphan*/  dev; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  bgmac_adjust_link ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct phy_device* fixed_phy_register (int /*<<< orphan*/ ,struct fixed_phy_status*,int /*<<< orphan*/ *) ; 
 int phy_connect_direct (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bgmac_phy_connect_direct(struct bgmac *bgmac)
{
	struct fixed_phy_status fphy_status = {
		.link = 1,
		.speed = SPEED_1000,
		.duplex = DUPLEX_FULL,
	};
	struct phy_device *phy_dev;
	int err;

	phy_dev = fixed_phy_register(PHY_POLL, &fphy_status, NULL);
	if (!phy_dev || IS_ERR(phy_dev)) {
		dev_err(bgmac->dev, "Failed to register fixed PHY device\n");
		return -ENODEV;
	}

	err = phy_connect_direct(bgmac->net_dev, phy_dev, bgmac_adjust_link,
				 PHY_INTERFACE_MODE_MII);
	if (err) {
		dev_err(bgmac->dev, "Connecting PHY failed\n");
		return err;
	}

	return err;
}