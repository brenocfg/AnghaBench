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
struct sdhci_host {int quirks; int quirks2; char* hw_name; int irq; struct sdhci_host* ioaddr; int /*<<< orphan*/ * ops; int /*<<< orphan*/  mmc; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct f_sdhost_priv {struct sdhci_host* clk_iface; struct sdhci_host* clk; int /*<<< orphan*/  vendor_hs200; int /*<<< orphan*/  enable_cmd_dat_delay; struct device* dev; } ;

/* Variables and functions */
 int F_SDH30_AHB_BIGED ; 
 int /*<<< orphan*/  F_SDH30_AHB_CONFIG ; 
 int F_SDH30_AHB_INCR_16 ; 
 int F_SDH30_AHB_INCR_4 ; 
 int F_SDH30_AHB_INCR_8 ; 
 int F_SDH30_BUSLOCK_EN ; 
 int /*<<< orphan*/  F_SDH30_EMMC_HS200 ; 
 int F_SDH30_EMMC_RST ; 
 int /*<<< orphan*/  F_SDH30_ESD_CONTROL ; 
 int F_SDH30_SIN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int SDHCI_CAN_DO_8BIT ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int SDHCI_QUIRK2_SUPPORT_SINGLE ; 
 int SDHCI_QUIRK2_TUNING_WORK_AROUND ; 
 int SDHCI_QUIRK_INVERTED_WRITE_PROTECT ; 
 int SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 scalar_t__ dev_of_node (struct device*) ; 
 int /*<<< orphan*/  device_property_read_bool (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct sdhci_host* devm_ioremap_resource (struct device*,struct resource*) ; 
 int mmc_of_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sdhci_host*) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 struct sdhci_host* sdhci_alloc_host (struct device*,int) ; 
 int /*<<< orphan*/  sdhci_f_sdh30_ops ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 struct f_sdhost_priv* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_f_sdh30_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int irq, ctrl = 0, ret = 0;
	struct f_sdhost_priv *priv;
	u32 reg = 0;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	host = sdhci_alloc_host(dev, sizeof(struct f_sdhost_priv));
	if (IS_ERR(host))
		return PTR_ERR(host);

	priv = sdhci_priv(host);
	priv->dev = dev;

	host->quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		       SDHCI_QUIRK_INVERTED_WRITE_PROTECT;
	host->quirks2 = SDHCI_QUIRK2_SUPPORT_SINGLE |
			SDHCI_QUIRK2_TUNING_WORK_AROUND;

	priv->enable_cmd_dat_delay = device_property_read_bool(dev,
						"fujitsu,cmd-dat-delay-select");

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto err;

	platform_set_drvdata(pdev, host);

	host->hw_name = "f_sdh30";
	host->ops = &sdhci_f_sdh30_ops;
	host->irq = irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(host->ioaddr)) {
		ret = PTR_ERR(host->ioaddr);
		goto err;
	}

	if (dev_of_node(dev)) {
		sdhci_get_of_property(pdev);

		priv->clk_iface = devm_clk_get(&pdev->dev, "iface");
		if (IS_ERR(priv->clk_iface)) {
			ret = PTR_ERR(priv->clk_iface);
			goto err;
		}

		ret = clk_prepare_enable(priv->clk_iface);
		if (ret)
			goto err;

		priv->clk = devm_clk_get(&pdev->dev, "core");
		if (IS_ERR(priv->clk)) {
			ret = PTR_ERR(priv->clk);
			goto err_clk;
		}

		ret = clk_prepare_enable(priv->clk);
		if (ret)
			goto err_clk;
	}

	/* init vendor specific regs */
	ctrl = sdhci_readw(host, F_SDH30_AHB_CONFIG);
	ctrl |= F_SDH30_SIN | F_SDH30_AHB_INCR_16 | F_SDH30_AHB_INCR_8 |
		F_SDH30_AHB_INCR_4;
	ctrl &= ~(F_SDH30_AHB_BIGED | F_SDH30_BUSLOCK_EN);
	sdhci_writew(host, ctrl, F_SDH30_AHB_CONFIG);

	reg = sdhci_readl(host, F_SDH30_ESD_CONTROL);
	sdhci_writel(host, reg & ~F_SDH30_EMMC_RST, F_SDH30_ESD_CONTROL);
	msleep(20);
	sdhci_writel(host, reg | F_SDH30_EMMC_RST, F_SDH30_ESD_CONTROL);

	reg = sdhci_readl(host, SDHCI_CAPABILITIES);
	if (reg & SDHCI_CAN_DO_8BIT)
		priv->vendor_hs200 = F_SDH30_EMMC_HS200;

	ret = sdhci_add_host(host);
	if (ret)
		goto err_add_host;

	return 0;

err_add_host:
	clk_disable_unprepare(priv->clk);
err_clk:
	clk_disable_unprepare(priv->clk_iface);
err:
	sdhci_free_host(host);
	return ret;
}