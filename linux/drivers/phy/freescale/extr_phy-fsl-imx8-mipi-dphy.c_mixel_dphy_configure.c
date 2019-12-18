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
union phy_configure_opts {int /*<<< orphan*/  mipi_dphy; } ;
struct phy {int dummy; } ;
struct mixel_dphy_priv {TYPE_1__* devdata; int /*<<< orphan*/  cfg; } ;
struct mixel_dphy_cfg {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_rxcdrp; int /*<<< orphan*/  reg_rxlprp; int /*<<< orphan*/  reg_auto_pd_en; int /*<<< orphan*/  reg_tx_rcal; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_LOCK_BYP ; 
 int /*<<< orphan*/  DPHY_TST ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mixel_dphy_cfg*,int) ; 
 int mixel_dphy_config_from_opts (struct phy*,int /*<<< orphan*/ *,struct mixel_dphy_cfg*) ; 
 int mixel_dphy_set_pll_params (struct phy*) ; 
 int /*<<< orphan*/  mixel_phy_set_hs_timings (struct phy*) ; 
 struct mixel_dphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_write (struct phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixel_dphy_configure(struct phy *phy, union phy_configure_opts *opts)
{
	struct mixel_dphy_priv *priv = phy_get_drvdata(phy);
	struct mixel_dphy_cfg cfg = { 0 };
	int ret;

	ret = mixel_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
	if (ret)
		return ret;

	/* Update the configuration */
	memcpy(&priv->cfg, &cfg, sizeof(struct mixel_dphy_cfg));

	phy_write(phy, 0x00, DPHY_LOCK_BYP);
	phy_write(phy, 0x01, priv->devdata->reg_tx_rcal);
	phy_write(phy, 0x00, priv->devdata->reg_auto_pd_en);
	phy_write(phy, 0x02, priv->devdata->reg_rxlprp);
	phy_write(phy, 0x02, priv->devdata->reg_rxcdrp);
	phy_write(phy, 0x25, DPHY_TST);

	mixel_phy_set_hs_timings(phy);
	ret = mixel_dphy_set_pll_params(phy);
	if (ret < 0)
		return ret;

	return 0;
}