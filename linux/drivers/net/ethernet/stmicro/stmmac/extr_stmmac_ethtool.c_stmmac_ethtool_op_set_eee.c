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
struct stmmac_priv {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_enabled; int /*<<< orphan*/  phylink; } ;
struct net_device {int dummy; } ;
struct ethtool_eee {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_set_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 
 int /*<<< orphan*/  stmmac_disable_eee_mode (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_eee_init (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_ethtool_op_set_eee(struct net_device *dev,
				     struct ethtool_eee *edata)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

	if (!edata->eee_enabled) {
		stmmac_disable_eee_mode(priv);
	} else {
		/* We are asking for enabling the EEE but it is safe
		 * to verify all by invoking the eee_init function.
		 * In case of failure it will return an error.
		 */
		edata->eee_enabled = stmmac_eee_init(priv);
		if (!edata->eee_enabled)
			return -EOPNOTSUPP;
	}

	ret = phylink_ethtool_set_eee(priv->phylink, edata);
	if (ret)
		return ret;

	priv->eee_enabled = edata->eee_enabled;
	priv->tx_lpi_timer = edata->tx_lpi_timer;
	return 0;
}