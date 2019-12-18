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
struct TYPE_2__ {scalar_t__ eee; } ;
struct stmmac_priv {int eee_active; int /*<<< orphan*/  hw; int /*<<< orphan*/  eee_enabled; TYPE_1__ dma_cap; int /*<<< orphan*/  ioaddr; } ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct phy_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_init_eee (struct phy_device*,int) ; 
 int /*<<< orphan*/  stmmac_eee_init (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_set (struct stmmac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stmmac_set_eee_pls (struct stmmac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_mac_link_up(struct phylink_config *config,
			       unsigned int mode, phy_interface_t interface,
			       struct phy_device *phy)
{
	struct stmmac_priv *priv = netdev_priv(to_net_dev(config->dev));

	stmmac_mac_set(priv, priv->ioaddr, true);
	if (phy && priv->dma_cap.eee) {
		priv->eee_active = phy_init_eee(phy, 1) >= 0;
		priv->eee_enabled = stmmac_eee_init(priv);
		stmmac_set_eee_pls(priv, priv->hw, true);
	}
}