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
struct sh_eth_private {int duplex; scalar_t__ speed; int /*<<< orphan*/  lock; scalar_t__ no_ether_link; TYPE_1__* cd; scalar_t__ link; } ;
struct phy_device {int duplex; scalar_t__ speed; scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;
struct TYPE_2__ {scalar_t__ no_psr; int /*<<< orphan*/  (* set_rate ) (struct net_device*) ;int /*<<< orphan*/  (* set_duplex ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_TXF ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct sh_eth_private*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_rcv_snd_disable (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_rcv_snd_enable (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static void sh_eth_adjust_link(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	unsigned long flags;
	int new_state = 0;

	spin_lock_irqsave(&mdp->lock, flags);

	/* Disable TX and RX right over here, if E-MAC change is ignored */
	if (mdp->cd->no_psr || mdp->no_ether_link)
		sh_eth_rcv_snd_disable(ndev);

	if (phydev->link) {
		if (phydev->duplex != mdp->duplex) {
			new_state = 1;
			mdp->duplex = phydev->duplex;
			if (mdp->cd->set_duplex)
				mdp->cd->set_duplex(ndev);
		}

		if (phydev->speed != mdp->speed) {
			new_state = 1;
			mdp->speed = phydev->speed;
			if (mdp->cd->set_rate)
				mdp->cd->set_rate(ndev);
		}
		if (!mdp->link) {
			sh_eth_modify(ndev, ECMR, ECMR_TXF, 0);
			new_state = 1;
			mdp->link = phydev->link;
		}
	} else if (mdp->link) {
		new_state = 1;
		mdp->link = 0;
		mdp->speed = 0;
		mdp->duplex = -1;
	}

	/* Enable TX and RX right over here, if E-MAC change is ignored */
	if ((mdp->cd->no_psr || mdp->no_ether_link) && phydev->link)
		sh_eth_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&mdp->lock, flags);

	if (new_state && netif_msg_link(mdp))
		phy_print_status(phydev);
}