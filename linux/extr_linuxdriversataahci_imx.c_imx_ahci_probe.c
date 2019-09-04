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
typedef  int u32 ;
struct device {scalar_t__ mmio; struct imx_ahci_priv* plat_data; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct imx_ahci_priv {int no_device; int first_time; int type; int phy_params; struct device* sata_clk; struct device* ahb_clk; struct device* gpr; struct device* sata_ref_clk; struct platform_device* ahci_pdev; } ;
struct ahci_host_priv {scalar_t__ mmio; struct imx_ahci_priv* plat_data; } ;
typedef  enum ahci_imx_type { ____Placeholder_ahci_imx_type } ahci_imx_type ;

/* Variables and functions */
 scalar_t__ AHCI_IMX53 ; 
 scalar_t__ AHCI_IMX6Q ; 
 scalar_t__ AHCI_IMX6QP ; 
 scalar_t__ AHCI_IMX8QM ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_HWMON ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HOST_CAP ; 
 unsigned int HOST_CAP_SSS ; 
 scalar_t__ HOST_PORTS_IMPL ; 
 int IMX6Q_GPR13_SATA_RX_DPLL_MODE_2P_4F ; 
 int IMX6Q_GPR13_SATA_RX_LOS_LVL_SATA2M ; 
 int IMX6Q_GPR13_SATA_SPD_MODE_3P0G ; 
 scalar_t__ IMX_TIMER1MS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  ahci_imx_port_info ; 
 struct device* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct device*) ; 
 int clk_get_rate (struct device*) ; 
 int clk_prepare_enable (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct device*,int /*<<< orphan*/ ) ; 
 struct imx_ahci_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_register (struct device*,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_sata_ahci_groups ; 
 int /*<<< orphan*/  fsl_sata_ahci_of_thermal_ops ; 
 int /*<<< orphan*/  gpr13_props ; 
 int imx8_sata_probe (struct device*,struct imx_ahci_priv*) ; 
 int /*<<< orphan*/  imx_ahci_of_match ; 
 int imx_ahci_parse_props (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_sata_disable (struct device*) ; 
 int imx_sata_enable (struct device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 unsigned int readl (scalar_t__) ; 
 struct device* syscon_regmap_lookup_by_compatible (char*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int imx_ahci_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *of_id;
	struct ahci_host_priv *hpriv;
	struct imx_ahci_priv *imxpriv;
	unsigned int reg_val;
	int ret;

	of_id = of_match_device(imx_ahci_of_match, dev);
	if (!of_id)
		return -EINVAL;

	imxpriv = devm_kzalloc(dev, sizeof(*imxpriv), GFP_KERNEL);
	if (!imxpriv)
		return -ENOMEM;

	imxpriv->ahci_pdev = pdev;
	imxpriv->no_device = false;
	imxpriv->first_time = true;
	imxpriv->type = (enum ahci_imx_type)of_id->data;

	imxpriv->sata_clk = devm_clk_get(dev, "sata");
	if (IS_ERR(imxpriv->sata_clk)) {
		dev_err(dev, "can't get sata clock.\n");
		return PTR_ERR(imxpriv->sata_clk);
	}

	imxpriv->sata_ref_clk = devm_clk_get(dev, "sata_ref");
	if (IS_ERR(imxpriv->sata_ref_clk)) {
		dev_err(dev, "can't get sata_ref clock.\n");
		return PTR_ERR(imxpriv->sata_ref_clk);
	}

	imxpriv->ahb_clk = devm_clk_get(dev, "ahb");
	if (IS_ERR(imxpriv->ahb_clk)) {
		dev_err(dev, "can't get ahb clock.\n");
		return PTR_ERR(imxpriv->ahb_clk);
	}

	if (imxpriv->type == AHCI_IMX6Q || imxpriv->type == AHCI_IMX6QP) {
		u32 reg_value;

		imxpriv->gpr = syscon_regmap_lookup_by_compatible(
							"fsl,imx6q-iomuxc-gpr");
		if (IS_ERR(imxpriv->gpr)) {
			dev_err(dev,
				"failed to find fsl,imx6q-iomux-gpr regmap\n");
			return PTR_ERR(imxpriv->gpr);
		}

		reg_value = imx_ahci_parse_props(dev, gpr13_props,
						 ARRAY_SIZE(gpr13_props));

		imxpriv->phy_params =
				   IMX6Q_GPR13_SATA_RX_LOS_LVL_SATA2M |
				   IMX6Q_GPR13_SATA_RX_DPLL_MODE_2P_4F |
				   IMX6Q_GPR13_SATA_SPD_MODE_3P0G |
				   reg_value;
	} else if (imxpriv->type == AHCI_IMX8QM) {
		ret =  imx8_sata_probe(dev, imxpriv);
		if (ret)
			return ret;
	}

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	hpriv->plat_data = imxpriv;

	ret = clk_prepare_enable(imxpriv->sata_clk);
	if (ret)
		return ret;

	if (imxpriv->type == AHCI_IMX53 &&
	    IS_ENABLED(CONFIG_HWMON)) {
		/* Add the temperature monitor */
		struct device *hwmon_dev;

		hwmon_dev =
			devm_hwmon_device_register_with_groups(dev,
							"sata_ahci",
							hpriv,
							fsl_sata_ahci_groups);
		if (IS_ERR(hwmon_dev)) {
			ret = PTR_ERR(hwmon_dev);
			goto disable_clk;
		}
		devm_thermal_zone_of_sensor_register(hwmon_dev, 0, hwmon_dev,
					     &fsl_sata_ahci_of_thermal_ops);
		dev_info(dev, "%s: sensor 'sata_ahci'\n", dev_name(hwmon_dev));
	}

	ret = imx_sata_enable(hpriv);
	if (ret)
		goto disable_clk;

	/*
	 * Configure the HWINIT bits of the HOST_CAP and HOST_PORTS_IMPL,
	 * and IP vendor specific register IMX_TIMER1MS.
	 * Configure CAP_SSS (support stagered spin up).
	 * Implement the port0.
	 * Get the ahb clock rate, and configure the TIMER1MS register.
	 */
	reg_val = readl(hpriv->mmio + HOST_CAP);
	if (!(reg_val & HOST_CAP_SSS)) {
		reg_val |= HOST_CAP_SSS;
		writel(reg_val, hpriv->mmio + HOST_CAP);
	}
	reg_val = readl(hpriv->mmio + HOST_PORTS_IMPL);
	if (!(reg_val & 0x1)) {
		reg_val |= 0x1;
		writel(reg_val, hpriv->mmio + HOST_PORTS_IMPL);
	}

	reg_val = clk_get_rate(imxpriv->ahb_clk) / 1000;
	writel(reg_val, hpriv->mmio + IMX_TIMER1MS);

	ret = ahci_platform_init_host(pdev, hpriv, &ahci_imx_port_info,
				      &ahci_platform_sht);
	if (ret)
		goto disable_sata;

	return 0;

disable_sata:
	imx_sata_disable(hpriv);
disable_clk:
	clk_disable_unprepare(imxpriv->sata_clk);
	return ret;
}