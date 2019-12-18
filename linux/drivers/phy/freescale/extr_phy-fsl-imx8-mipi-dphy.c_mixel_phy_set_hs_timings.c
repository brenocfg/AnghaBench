#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxhs_settle; int /*<<< orphan*/  mc_prg_hs_trail; int /*<<< orphan*/  m_prg_hs_trail; int /*<<< orphan*/  mc_prg_hs_zero; int /*<<< orphan*/  m_prg_hs_zero; int /*<<< orphan*/  mc_prg_hs_prepare; int /*<<< orphan*/  m_prg_hs_prepare; } ;
struct mixel_dphy_priv {TYPE_1__* devdata; TYPE_2__ cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_rxhs_settle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_MC_PRG_HS_PREPARE ; 
 int /*<<< orphan*/  DPHY_MC_PRG_HS_TRAIL ; 
 int /*<<< orphan*/  DPHY_MC_PRG_HS_ZERO ; 
 int /*<<< orphan*/  DPHY_M_PRG_HS_PREPARE ; 
 int /*<<< orphan*/  DPHY_M_PRG_HS_TRAIL ; 
 int /*<<< orphan*/  DPHY_M_PRG_HS_ZERO ; 
 struct mixel_dphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_write (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixel_phy_set_hs_timings(struct phy *phy)
{
	struct mixel_dphy_priv *priv = phy_get_drvdata(phy);

	phy_write(phy, priv->cfg.m_prg_hs_prepare, DPHY_M_PRG_HS_PREPARE);
	phy_write(phy, priv->cfg.mc_prg_hs_prepare, DPHY_MC_PRG_HS_PREPARE);
	phy_write(phy, priv->cfg.m_prg_hs_zero, DPHY_M_PRG_HS_ZERO);
	phy_write(phy, priv->cfg.mc_prg_hs_zero, DPHY_MC_PRG_HS_ZERO);
	phy_write(phy, priv->cfg.m_prg_hs_trail, DPHY_M_PRG_HS_TRAIL);
	phy_write(phy, priv->cfg.mc_prg_hs_trail, DPHY_MC_PRG_HS_TRAIL);
	phy_write(phy, priv->cfg.rxhs_settle, priv->devdata->reg_rxhs_settle);
}