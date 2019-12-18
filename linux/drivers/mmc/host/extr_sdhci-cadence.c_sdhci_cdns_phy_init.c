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
struct sdhci_cdns_priv {int nr_phy_params; TYPE_1__* phy_params; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int sdhci_cdns_write_phy_reg (struct sdhci_cdns_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_cdns_phy_init(struct sdhci_cdns_priv *priv)
{
	int ret, i;

	for (i = 0; i < priv->nr_phy_params; i++) {
		ret = sdhci_cdns_write_phy_reg(priv, priv->phy_params[i].addr,
					       priv->phy_params[i].data);
		if (ret)
			return ret;
	}

	return 0;
}