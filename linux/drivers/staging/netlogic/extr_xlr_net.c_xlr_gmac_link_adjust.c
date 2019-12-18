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
typedef  int /*<<< orphan*/  u32 ;
struct xlr_net_priv {scalar_t__ phy_speed; int /*<<< orphan*/  port_id; int /*<<< orphan*/  base_addr; } ;
struct phy_device {scalar_t__ speed; scalar_t__ link; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_INTREG ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct phy_device* xlr_get_phydev (struct xlr_net_priv*) ; 
 int /*<<< orphan*/  xlr_nae_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_set_gmac_speed (struct xlr_net_priv*) ; 

__attribute__((used)) static void xlr_gmac_link_adjust(struct net_device *ndev)
{
	struct xlr_net_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = xlr_get_phydev(priv);
	u32 intreg;

	intreg = xlr_nae_rdreg(priv->base_addr, R_INTREG);
	if (phydev->link) {
		if (phydev->speed != priv->phy_speed) {
			xlr_set_gmac_speed(priv);
			pr_info("gmac%d : Link up\n", priv->port_id);
		}
	} else {
		xlr_set_gmac_speed(priv);
		pr_info("gmac%d : Link down\n", priv->port_id);
	}
}