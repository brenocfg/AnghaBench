#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int irq; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct net_device {int dummy; } ;
struct macb_platform_data {int /*<<< orphan*/  phy_irq_pin; } ;
struct macb {int caps; int duplex; scalar_t__ speed; scalar_t__ link; int /*<<< orphan*/  phy_interface; TYPE_1__* pdev; int /*<<< orphan*/  mii_bus; scalar_t__ phy_node; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int MACB_CAPS_GIGABIT_MODE_AVAILABLE ; 
 int MACB_CAPS_NO_GIGABIT_HALF ; 
 int /*<<< orphan*/  PHY_BASIC_FEATURES ; 
 int /*<<< orphan*/  PHY_GBIT_FEATURES ; 
 int PHY_MAX_ADDR ; 
 int PHY_POLL ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 struct macb_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int devm_gpio_request (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_handle_link_change ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 struct phy_device* mdiobus_scan (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 scalar_t__ of_node_get (struct device_node*) ; 
 scalar_t__ of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macb_mii_probe(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	struct macb_platform_data *pdata;
	struct phy_device *phydev;
	struct device_node *np;
	int phy_irq, ret, i;

	pdata = dev_get_platdata(&bp->pdev->dev);
	np = bp->pdev->dev.of_node;
	ret = 0;

	if (np) {
		if (of_phy_is_fixed_link(np)) {
			bp->phy_node = of_node_get(np);
		} else {
			bp->phy_node = of_parse_phandle(np, "phy-handle", 0);
			/* fallback to standard phy registration if no
			 * phy-handle was found nor any phy found during
			 * dt phy registration
			 */
			if (!bp->phy_node && !phy_find_first(bp->mii_bus)) {
				for (i = 0; i < PHY_MAX_ADDR; i++) {
					struct phy_device *phydev;

					phydev = mdiobus_scan(bp->mii_bus, i);
					if (IS_ERR(phydev) &&
					    PTR_ERR(phydev) != -ENODEV) {
						ret = PTR_ERR(phydev);
						break;
					}
				}

				if (ret)
					return -ENODEV;
			}
		}
	}

	if (bp->phy_node) {
		phydev = of_phy_connect(dev, bp->phy_node,
					&macb_handle_link_change, 0,
					bp->phy_interface);
		if (!phydev)
			return -ENODEV;
	} else {
		phydev = phy_find_first(bp->mii_bus);
		if (!phydev) {
			netdev_err(dev, "no PHY found\n");
			return -ENXIO;
		}

		if (pdata) {
			if (gpio_is_valid(pdata->phy_irq_pin)) {
				ret = devm_gpio_request(&bp->pdev->dev,
							pdata->phy_irq_pin, "phy int");
				if (!ret) {
					phy_irq = gpio_to_irq(pdata->phy_irq_pin);
					phydev->irq = (phy_irq < 0) ? PHY_POLL : phy_irq;
				}
			} else {
				phydev->irq = PHY_POLL;
			}
		}

		/* attach the mac to the phy */
		ret = phy_connect_direct(dev, phydev, &macb_handle_link_change,
					 bp->phy_interface);
		if (ret) {
			netdev_err(dev, "Could not attach to PHY\n");
			return ret;
		}
	}

	/* mask with MAC supported features */
	if (macb_is_gem(bp) && bp->caps & MACB_CAPS_GIGABIT_MODE_AVAILABLE)
		phydev->supported &= PHY_GBIT_FEATURES;
	else
		phydev->supported &= PHY_BASIC_FEATURES;

	if (bp->caps & MACB_CAPS_NO_GIGABIT_HALF)
		phydev->supported &= ~SUPPORTED_1000baseT_Half;

	phydev->advertising = phydev->supported;

	bp->link = 0;
	bp->speed = 0;
	bp->duplex = -1;

	return 0;
}