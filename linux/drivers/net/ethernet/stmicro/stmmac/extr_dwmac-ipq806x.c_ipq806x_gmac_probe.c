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
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct plat_stmmacenet_data {int has_gmac; int /*<<< orphan*/  fix_mac_speed; struct ipq806x_gmac* bsp_priv; } ;
struct ipq806x_gmac {int phy_mode; int /*<<< orphan*/  id; int /*<<< orphan*/  qsgmii_csr; int /*<<< orphan*/  nss_common; struct platform_device* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  NSS_COMMON_CLK_GATE ; 
 int NSS_COMMON_CLK_GATE_PTP_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSS_COMMON_CLK_SRC_CTRL ; 
 int NSS_COMMON_CLK_SRC_CTRL_OFFSET (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_CLK_SRC_CTRL_RGMII (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_CLK_SRC_CTRL_SGMII (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSS_COMMON_GMAC_CTL (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_GMAC_CTL_CSYS_REQ ; 
 int NSS_COMMON_GMAC_CTL_IFG_LIMIT_OFFSET ; 
 int NSS_COMMON_GMAC_CTL_IFG_OFFSET ; 
 int NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  QSGMII_PCS_CAL_LCKDT_CTL ; 
 int QSGMII_PCS_CAL_LCKDT_CTL_RST ; 
 int QSGMII_PHY_CDR_EN ; 
 int QSGMII_PHY_CDR_PI_SLEW_OFFSET ; 
 int QSGMII_PHY_PHASE_LOOP_GAIN_OFFSET ; 
 int QSGMII_PHY_QSGMII_EN ; 
 int QSGMII_PHY_RX_DC_BIAS_OFFSET ; 
 int QSGMII_PHY_RX_FRONT_EN ; 
 int QSGMII_PHY_RX_INPUT_EQU_OFFSET ; 
 int QSGMII_PHY_RX_SIGNAL_DETECT_EN ; 
 int /*<<< orphan*/  QSGMII_PHY_SGMII_CTL (int /*<<< orphan*/ ) ; 
 int QSGMII_PHY_TX_DRIVER_EN ; 
 int QSGMII_PHY_TX_DRV_AMP_OFFSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ipq806x_gmac* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipq806x_gmac_fix_mac_speed ; 
 int ipq806x_gmac_of_parse (struct ipq806x_gmac*) ; 
 int /*<<< orphan*/  phy_modes (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stmmac_dvr_probe (struct device*,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int ipq806x_gmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct device *dev = &pdev->dev;
	struct ipq806x_gmac *gmac;
	int val;
	int err;

	val = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (val)
		return val;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	gmac = devm_kzalloc(dev, sizeof(*gmac), GFP_KERNEL);
	if (!gmac) {
		err = -ENOMEM;
		goto err_remove_config_dt;
	}

	gmac->pdev = pdev;

	err = ipq806x_gmac_of_parse(gmac);
	if (err) {
		dev_err(dev, "device tree parsing error\n");
		goto err_remove_config_dt;
	}

	regmap_write(gmac->qsgmii_csr, QSGMII_PCS_CAL_LCKDT_CTL,
		     QSGMII_PCS_CAL_LCKDT_CTL_RST);

	/* Inter frame gap is set to 12 */
	val = 12 << NSS_COMMON_GMAC_CTL_IFG_OFFSET |
	      12 << NSS_COMMON_GMAC_CTL_IFG_LIMIT_OFFSET;
	/* We also initiate an AXI low power exit request */
	val |= NSS_COMMON_GMAC_CTL_CSYS_REQ;
	switch (gmac->phy_mode) {
	case PHY_INTERFACE_MODE_RGMII:
		val |= NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL;
		break;
	case PHY_INTERFACE_MODE_SGMII:
		val &= ~NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL;
		break;
	default:
		dev_err(&pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		err = -EINVAL;
		goto err_remove_config_dt;
	}
	regmap_write(gmac->nss_common, NSS_COMMON_GMAC_CTL(gmac->id), val);

	/* Configure the clock src according to the mode */
	regmap_read(gmac->nss_common, NSS_COMMON_CLK_SRC_CTRL, &val);
	val &= ~(1 << NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id));
	switch (gmac->phy_mode) {
	case PHY_INTERFACE_MODE_RGMII:
		val |= NSS_COMMON_CLK_SRC_CTRL_RGMII(gmac->id) <<
			NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id);
		break;
	case PHY_INTERFACE_MODE_SGMII:
		val |= NSS_COMMON_CLK_SRC_CTRL_SGMII(gmac->id) <<
			NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id);
		break;
	default:
		dev_err(&pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		err = -EINVAL;
		goto err_remove_config_dt;
	}
	regmap_write(gmac->nss_common, NSS_COMMON_CLK_SRC_CTRL, val);

	/* Enable PTP clock */
	regmap_read(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val |= NSS_COMMON_CLK_GATE_PTP_EN(gmac->id);
	regmap_write(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	if (gmac->phy_mode == PHY_INTERFACE_MODE_SGMII) {
		regmap_write(gmac->qsgmii_csr, QSGMII_PHY_SGMII_CTL(gmac->id),
			     QSGMII_PHY_CDR_EN |
			     QSGMII_PHY_RX_FRONT_EN |
			     QSGMII_PHY_RX_SIGNAL_DETECT_EN |
			     QSGMII_PHY_TX_DRIVER_EN |
			     QSGMII_PHY_QSGMII_EN |
			     0x4ul << QSGMII_PHY_PHASE_LOOP_GAIN_OFFSET |
			     0x3ul << QSGMII_PHY_RX_DC_BIAS_OFFSET |
			     0x1ul << QSGMII_PHY_RX_INPUT_EQU_OFFSET |
			     0x2ul << QSGMII_PHY_CDR_PI_SLEW_OFFSET |
			     0xCul << QSGMII_PHY_TX_DRV_AMP_OFFSET);
	}

	plat_dat->has_gmac = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->fix_mac_speed = ipq806x_gmac_fix_mac_speed;

	err = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (err)
		goto err_remove_config_dt;

	return 0;

err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return err;
}