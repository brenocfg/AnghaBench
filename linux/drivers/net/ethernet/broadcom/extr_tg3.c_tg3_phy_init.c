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
struct tg3 {int phy_flags; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  mdio_bus; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
struct phy_device {int interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
#define  PHY_INTERFACE_MODE_GMII 130 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_RGMII 128 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int TG3_PHYFLG_10_100_ONLY ; 
 int TG3_PHYFLG_IS_CONNECTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  tg3_adjust_link ; 
 int /*<<< orphan*/  tg3_bmcr_reset (struct tg3*) ; 

__attribute__((used)) static int tg3_phy_init(struct tg3 *tp)
{
	struct phy_device *phydev;

	if (tp->phy_flags & TG3_PHYFLG_IS_CONNECTED)
		return 0;

	/* Bring the PHY back to a known state. */
	tg3_bmcr_reset(tp);

	phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	/* Attach the MAC to the PHY. */
	phydev = phy_connect(tp->dev, phydev_name(phydev),
			     tg3_adjust_link, phydev->interface);
	if (IS_ERR(phydev)) {
		dev_err(&tp->pdev->dev, "Could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	/* Mask with MAC supported features. */
	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_GMII:
	case PHY_INTERFACE_MODE_RGMII:
		if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
			phy_set_max_speed(phydev, SPEED_1000);
			phy_support_asym_pause(phydev);
			break;
		}
		/* fall through */
	case PHY_INTERFACE_MODE_MII:
		phy_set_max_speed(phydev, SPEED_100);
		phy_support_asym_pause(phydev);
		break;
	default:
		phy_disconnect(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
		return -EINVAL;
	}

	tp->phy_flags |= TG3_PHYFLG_IS_CONNECTED;

	phy_attached_info(phydev);

	return 0;
}