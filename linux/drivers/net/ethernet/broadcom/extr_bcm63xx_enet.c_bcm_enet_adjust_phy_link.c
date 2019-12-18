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
struct phy_device {scalar_t__ link; scalar_t__ duplex; int pause; int /*<<< orphan*/  speed; } ;
struct net_device {int /*<<< orphan*/  name; struct phy_device* phydev; } ;
struct bcm_enet_priv {scalar_t__ old_link; scalar_t__ old_duplex; int old_pause; int pause_rx; int pause_tx; int /*<<< orphan*/  pause_auto; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  bcm_enet_set_duplex (struct bcm_enet_priv*,int) ; 
 int /*<<< orphan*/  bcm_enet_set_flow (struct bcm_enet_priv*,int,int) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void bcm_enet_adjust_phy_link(struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct phy_device *phydev;
	int status_changed;

	priv = netdev_priv(dev);
	phydev = dev->phydev;
	status_changed = 0;

	if (priv->old_link != phydev->link) {
		status_changed = 1;
		priv->old_link = phydev->link;
	}

	/* reflect duplex change in mac configuration */
	if (phydev->link && phydev->duplex != priv->old_duplex) {
		bcm_enet_set_duplex(priv,
				    (phydev->duplex == DUPLEX_FULL) ? 1 : 0);
		status_changed = 1;
		priv->old_duplex = phydev->duplex;
	}

	/* enable flow control if remote advertise it (trust phylib to
	 * check that duplex is full */
	if (phydev->link && phydev->pause != priv->old_pause) {
		int rx_pause_en, tx_pause_en;

		if (phydev->pause) {
			/* pause was advertised by lpa and us */
			rx_pause_en = 1;
			tx_pause_en = 1;
		} else if (!priv->pause_auto) {
			/* pause setting overridden by user */
			rx_pause_en = priv->pause_rx;
			tx_pause_en = priv->pause_tx;
		} else {
			rx_pause_en = 0;
			tx_pause_en = 0;
		}

		bcm_enet_set_flow(priv, rx_pause_en, tx_pause_en);
		status_changed = 1;
		priv->old_pause = phydev->pause;
	}

	if (status_changed) {
		pr_info("%s: link %s", dev->name, phydev->link ?
			"UP" : "DOWN");
		if (phydev->link)
			pr_cont(" - %d/%s - flow control %s", phydev->speed,
			       DUPLEX_FULL == phydev->duplex ? "full" : "half",
			       phydev->pause == 1 ? "rx&tx" : "off");

		pr_cont("\n");
	}
}