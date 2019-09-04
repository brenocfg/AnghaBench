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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int speed; int advertising; scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ duplex; scalar_t__ link; int /*<<< orphan*/  interface; } ;
struct mt7530_priv {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_ASYM ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_CAP ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LPA_PAUSE_ASYM ; 
 int /*<<< orphan*/  LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MT7530_PMCR_P (int) ; 
 int PMCR_FORCE_FDX ; 
 int PMCR_FORCE_LNK ; 
 int PMCR_FORCE_MODE ; 
 int PMCR_FORCE_SPEED_100 ; 
 int PMCR_FORCE_SPEED_1000 ; 
 int PMCR_RX_FC_EN ; 
 int PMCR_TX_FC_EN ; 
 int PMCR_USERP_LINK ; 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_pad_clk_setup (struct dsa_switch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7623_pad_clk_setup (struct dsa_switch*) ; 
 scalar_t__ phy_is_pseudo_fixed_link (struct phy_device*) ; 

__attribute__((used)) static void mt7530_adjust_link(struct dsa_switch *ds, int port,
			       struct phy_device *phydev)
{
	struct mt7530_priv *priv = ds->priv;

	if (phy_is_pseudo_fixed_link(phydev)) {
		dev_dbg(priv->dev, "phy-mode for master device = %x\n",
			phydev->interface);

		/* Setup TX circuit incluing relevant PAD and driving */
		mt7530_pad_clk_setup(ds, phydev->interface);

		/* Setup RX circuit, relevant PAD and driving on the host
		 * which must be placed after the setup on the device side is
		 * all finished.
		 */
		mt7623_pad_clk_setup(ds);
	} else {
		u16 lcl_adv = 0, rmt_adv = 0;
		u8 flowctrl;
		u32 mcr = PMCR_USERP_LINK | PMCR_FORCE_MODE;

		switch (phydev->speed) {
		case SPEED_1000:
			mcr |= PMCR_FORCE_SPEED_1000;
			break;
		case SPEED_100:
			mcr |= PMCR_FORCE_SPEED_100;
			break;
		};

		if (phydev->link)
			mcr |= PMCR_FORCE_LNK;

		if (phydev->duplex) {
			mcr |= PMCR_FORCE_FDX;

			if (phydev->pause)
				rmt_adv = LPA_PAUSE_CAP;
			if (phydev->asym_pause)
				rmt_adv |= LPA_PAUSE_ASYM;

			if (phydev->advertising & ADVERTISED_Pause)
				lcl_adv |= ADVERTISE_PAUSE_CAP;
			if (phydev->advertising & ADVERTISED_Asym_Pause)
				lcl_adv |= ADVERTISE_PAUSE_ASYM;

			flowctrl = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);

			if (flowctrl & FLOW_CTRL_TX)
				mcr |= PMCR_TX_FC_EN;
			if (flowctrl & FLOW_CTRL_RX)
				mcr |= PMCR_RX_FC_EN;
		}
		mt7530_write(priv, MT7530_PMCR_P(port), mcr);
	}
}