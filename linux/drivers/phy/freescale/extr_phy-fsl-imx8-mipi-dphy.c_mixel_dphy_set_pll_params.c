#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_2__ dev; } ;
struct TYPE_4__ {int cm; int cn; int co; } ;
struct mixel_dphy_priv {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM (int) ; 
 int /*<<< orphan*/  CN (int) ; 
 int /*<<< orphan*/  CO (int) ; 
 int /*<<< orphan*/  DPHY_CM ; 
 int /*<<< orphan*/  DPHY_CN ; 
 int /*<<< orphan*/  DPHY_CO ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,int,int) ; 
 struct mixel_dphy_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixel_dphy_set_pll_params(struct phy *phy)
{
	struct mixel_dphy_priv *priv = dev_get_drvdata(phy->dev.parent);

	if (priv->cfg.cm < 16 || priv->cfg.cm > 255 ||
	    priv->cfg.cn < 1 || priv->cfg.cn > 32 ||
	    priv->cfg.co < 1 || priv->cfg.co > 8) {
		dev_err(&phy->dev, "Invalid CM/CN/CO values! (%u/%u/%u)\n",
			priv->cfg.cm, priv->cfg.cn, priv->cfg.co);
		return -EINVAL;
	}
	dev_dbg(&phy->dev, "Using CM:%u CN:%u CO:%u\n",
		priv->cfg.cm, priv->cfg.cn, priv->cfg.co);
	phy_write(phy, CM(priv->cfg.cm), DPHY_CM);
	phy_write(phy, CN(priv->cfg.cn), DPHY_CN);
	phy_write(phy, CO(priv->cfg.co), DPHY_CO);
	return 0;
}