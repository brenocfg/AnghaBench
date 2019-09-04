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
struct net_device {int flags; } ;
struct moxart_mac_priv_t {int /*<<< orphan*/  txlock; scalar_t__ base; int /*<<< orphan*/  reg_maccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_MULTI_EN ; 
 int IFF_ALLMULTI ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RCV_ALL ; 
 scalar_t__ REG_MAC_CTRL ; 
 int /*<<< orphan*/  RX_MULTIPKT ; 
 int /*<<< orphan*/  moxart_mac_setmulticast (struct net_device*) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void moxart_mac_set_rx_mode(struct net_device *ndev)
{
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);

	spin_lock_irq(&priv->txlock);

	(ndev->flags & IFF_PROMISC) ? (priv->reg_maccr |= RCV_ALL) :
				      (priv->reg_maccr &= ~RCV_ALL);

	(ndev->flags & IFF_ALLMULTI) ? (priv->reg_maccr |= RX_MULTIPKT) :
				       (priv->reg_maccr &= ~RX_MULTIPKT);

	if ((ndev->flags & IFF_MULTICAST) && netdev_mc_count(ndev)) {
		priv->reg_maccr |= HT_MULTI_EN;
		moxart_mac_setmulticast(ndev);
	} else {
		priv->reg_maccr &= ~HT_MULTI_EN;
	}

	writel(priv->reg_maccr, priv->base + REG_MAC_CTRL);

	spin_unlock_irq(&priv->txlock);
}