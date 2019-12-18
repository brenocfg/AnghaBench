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
typedef  int u16 ;
struct netsec_priv {TYPE_1__* desc_ring; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  mii_bus; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_NUM ; 
 int /*<<< orphan*/  MII_BMCR ; 
 size_t NETSEC_RING_RX ; 
 size_t NETSEC_RING_TX ; 
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int netsec_alloc_dring (struct netsec_priv*,size_t) ; 
 int /*<<< orphan*/  netsec_free_dring (struct netsec_priv*,size_t) ; 
 int netsec_phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netsec_phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int netsec_reset_hardware (struct netsec_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netsec_netdev_init(struct net_device *ndev)
{
	struct netsec_priv *priv = netdev_priv(ndev);
	int ret;
	u16 data;

	BUILD_BUG_ON_NOT_POWER_OF_2(DESC_NUM);

	ret = netsec_alloc_dring(priv, NETSEC_RING_TX);
	if (ret)
		return ret;

	ret = netsec_alloc_dring(priv, NETSEC_RING_RX);
	if (ret)
		goto err1;

	/* set phy power down */
	data = netsec_phy_read(priv->mii_bus, priv->phy_addr, MII_BMCR) |
		BMCR_PDOWN;
	netsec_phy_write(priv->mii_bus, priv->phy_addr, MII_BMCR, data);

	ret = netsec_reset_hardware(priv, true);
	if (ret)
		goto err2;

	spin_lock_init(&priv->desc_ring[NETSEC_RING_TX].lock);
	spin_lock_init(&priv->desc_ring[NETSEC_RING_RX].lock);

	return 0;
err2:
	netsec_free_dring(priv, NETSEC_RING_RX);
err1:
	netsec_free_dring(priv, NETSEC_RING_TX);
	return ret;
}