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
struct ravb_private {scalar_t__ speed; int /*<<< orphan*/  lock; scalar_t__ no_avb_link; scalar_t__ link; } ;
struct phy_device {scalar_t__ speed; scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_TXF ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct ravb_private*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_rcv_snd_disable (struct net_device*) ; 
 int /*<<< orphan*/  ravb_rcv_snd_enable (struct net_device*) ; 
 int /*<<< orphan*/  ravb_set_rate (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ravb_adjust_link(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	bool new_state = false;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Disable TX and RX right over here, if E-MAC change is ignored */
	if (priv->no_avb_link)
		ravb_rcv_snd_disable(ndev);

	if (phydev->link) {
		if (phydev->speed != priv->speed) {
			new_state = true;
			priv->speed = phydev->speed;
			ravb_set_rate(ndev);
		}
		if (!priv->link) {
			ravb_modify(ndev, ECMR, ECMR_TXF, 0);
			new_state = true;
			priv->link = phydev->link;
		}
	} else if (priv->link) {
		new_state = true;
		priv->link = 0;
		priv->speed = 0;
	}

	/* Enable TX and RX right over here, if E-MAC change is ignored */
	if (priv->no_avb_link && phydev->link)
		ravb_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&priv->lock, flags);

	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);
}