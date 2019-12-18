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
struct phy_device {int speed; int pause; scalar_t__ duplex; scalar_t__ asym_pause; int /*<<< orphan*/  link; } ;
struct net_device {struct phy_device* phydev; } ;
struct ftgmac100 {int rx_pause; int tx_pause; int cur_speed; scalar_t__ cur_duplex; int /*<<< orphan*/  reset_task; scalar_t__ base; scalar_t__ aneg_pause; } ;

/* Variables and functions */
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftgmac100_adjust_link(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;
	bool tx_pause, rx_pause;
	int new_speed;

	/* We store "no link" as speed 0 */
	if (!phydev->link)
		new_speed = 0;
	else
		new_speed = phydev->speed;

	/* Grab pause settings from PHY if configured to do so */
	if (priv->aneg_pause) {
		rx_pause = tx_pause = phydev->pause;
		if (phydev->asym_pause)
			tx_pause = !rx_pause;
	} else {
		rx_pause = priv->rx_pause;
		tx_pause = priv->tx_pause;
	}

	/* Link hasn't changed, do nothing */
	if (phydev->speed == priv->cur_speed &&
	    phydev->duplex == priv->cur_duplex &&
	    rx_pause == priv->rx_pause &&
	    tx_pause == priv->tx_pause)
		return;

	/* Print status if we have a link or we had one and just lost it,
	 * don't print otherwise.
	 */
	if (new_speed || priv->cur_speed)
		phy_print_status(phydev);

	priv->cur_speed = new_speed;
	priv->cur_duplex = phydev->duplex;
	priv->rx_pause = rx_pause;
	priv->tx_pause = tx_pause;

	/* Link is down, do nothing else */
	if (!new_speed)
		return;

	/* Disable all interrupts */
	iowrite32(0, priv->base + FTGMAC100_OFFSET_IER);

	/* Reset the adapter asynchronously */
	schedule_work(&priv->reset_task);
}