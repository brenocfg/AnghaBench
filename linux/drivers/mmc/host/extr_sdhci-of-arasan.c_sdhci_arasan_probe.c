#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct TYPE_8__ {int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  hs400_enhanced_strobe; } ;
struct sdhci_host {TYPE_4__* mmc; TYPE_1__ mmc_host_ops; } ;
struct sdhci_arasan_of_data {int /*<<< orphan*/  soc_ctl_map; int /*<<< orphan*/  pdata; } ;
struct sdhci_arasan_data {int has_cqe; struct sdhci_host* clk_ahb; struct sdhci_host* phy; int /*<<< orphan*/  quirks; struct sdhci_host* soc_ctl_base; int /*<<< orphan*/  soc_ctl_map; struct sdhci_host* host; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct sdhci_arasan_of_data* data; } ;
struct device_node {int dummy; } ;
struct clk {TYPE_4__* mmc; TYPE_1__ mmc_host_ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  caps2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int EPROBE_DEFER ; 
 struct sdhci_host* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  MMC_CAP2_CQE ; 
 int /*<<< orphan*/  MMC_CAP2_CQE_DCMD ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  SDHCI_ARASAN_QUIRK_CLOCK_UNSTABLE ; 
 int /*<<< orphan*/  SDHCI_ARASAN_QUIRK_FORCE_CDTEST ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct sdhci_host* devm_phy_get (TYPE_2__*,char*) ; 
 int mmc_of_parse (TYPE_4__*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  phy_exit (struct sdhci_host*) ; 
 int phy_init (struct sdhci_host*) ; 
 int sdhci_arasan_add_host (struct sdhci_arasan_data*) ; 
 int /*<<< orphan*/  sdhci_arasan_hs400_enhanced_strobe ; 
 int /*<<< orphan*/  sdhci_arasan_of_match ; 
 int sdhci_arasan_register_sdclk (struct sdhci_arasan_data*,struct sdhci_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  sdhci_arasan_unregister_sdclk (TYPE_2__*) ; 
 int /*<<< orphan*/  sdhci_arasan_update_baseclkfreq (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_arasan_update_clockmultiplier (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_arasan_voltage_switch ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct sdhci_arasan_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 struct sdhci_host* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int sdhci_arasan_probe(struct platform_device *pdev)
{
	int ret;
	const struct of_device_id *match;
	struct device_node *node;
	struct clk *clk_xin;
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_arasan_data *sdhci_arasan;
	struct device_node *np = pdev->dev.of_node;
	const struct sdhci_arasan_of_data *data;

	match = of_match_node(sdhci_arasan_of_match, pdev->dev.of_node);
	data = match->data;
	host = sdhci_pltfm_init(pdev, data->pdata, sizeof(*sdhci_arasan));

	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	sdhci_arasan->host = host;

	sdhci_arasan->soc_ctl_map = data->soc_ctl_map;

	node = of_parse_phandle(pdev->dev.of_node, "arasan,soc-ctl-syscon", 0);
	if (node) {
		sdhci_arasan->soc_ctl_base = syscon_node_to_regmap(node);
		of_node_put(node);

		if (IS_ERR(sdhci_arasan->soc_ctl_base)) {
			ret = PTR_ERR(sdhci_arasan->soc_ctl_base);
			if (ret != -EPROBE_DEFER)
				dev_err(&pdev->dev, "Can't get syscon: %d\n",
					ret);
			goto err_pltfm_free;
		}
	}

	sdhci_arasan->clk_ahb = devm_clk_get(&pdev->dev, "clk_ahb");
	if (IS_ERR(sdhci_arasan->clk_ahb)) {
		dev_err(&pdev->dev, "clk_ahb clock not found.\n");
		ret = PTR_ERR(sdhci_arasan->clk_ahb);
		goto err_pltfm_free;
	}

	clk_xin = devm_clk_get(&pdev->dev, "clk_xin");
	if (IS_ERR(clk_xin)) {
		dev_err(&pdev->dev, "clk_xin clock not found.\n");
		ret = PTR_ERR(clk_xin);
		goto err_pltfm_free;
	}

	ret = clk_prepare_enable(sdhci_arasan->clk_ahb);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable AHB clock.\n");
		goto err_pltfm_free;
	}

	ret = clk_prepare_enable(clk_xin);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable SD clock.\n");
		goto clk_dis_ahb;
	}

	sdhci_get_of_property(pdev);

	if (of_property_read_bool(np, "xlnx,fails-without-test-cd"))
		sdhci_arasan->quirks |= SDHCI_ARASAN_QUIRK_FORCE_CDTEST;

	if (of_property_read_bool(np, "xlnx,int-clock-stable-broken"))
		sdhci_arasan->quirks |= SDHCI_ARASAN_QUIRK_CLOCK_UNSTABLE;

	pltfm_host->clk = clk_xin;

	if (of_device_is_compatible(pdev->dev.of_node,
				    "rockchip,rk3399-sdhci-5.1"))
		sdhci_arasan_update_clockmultiplier(host, 0x0);

	sdhci_arasan_update_baseclkfreq(host);

	ret = sdhci_arasan_register_sdclk(sdhci_arasan, clk_xin, &pdev->dev);
	if (ret)
		goto clk_disable_all;

	ret = mmc_of_parse(host->mmc);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "parsing dt failed (%d)\n", ret);
		goto unreg_clk;
	}

	sdhci_arasan->phy = ERR_PTR(-ENODEV);
	if (of_device_is_compatible(pdev->dev.of_node,
				    "arasan,sdhci-5.1")) {
		sdhci_arasan->phy = devm_phy_get(&pdev->dev,
						 "phy_arasan");
		if (IS_ERR(sdhci_arasan->phy)) {
			ret = PTR_ERR(sdhci_arasan->phy);
			dev_err(&pdev->dev, "No phy for arasan,sdhci-5.1.\n");
			goto unreg_clk;
		}

		ret = phy_init(sdhci_arasan->phy);
		if (ret < 0) {
			dev_err(&pdev->dev, "phy_init err.\n");
			goto unreg_clk;
		}

		host->mmc_host_ops.hs400_enhanced_strobe =
					sdhci_arasan_hs400_enhanced_strobe;
		host->mmc_host_ops.start_signal_voltage_switch =
					sdhci_arasan_voltage_switch;
		sdhci_arasan->has_cqe = true;
		host->mmc->caps2 |= MMC_CAP2_CQE;

		if (!of_property_read_bool(np, "disable-cqe-dcmd"))
			host->mmc->caps2 |= MMC_CAP2_CQE_DCMD;
	}

	ret = sdhci_arasan_add_host(sdhci_arasan);
	if (ret)
		goto err_add_host;

	return 0;

err_add_host:
	if (!IS_ERR(sdhci_arasan->phy))
		phy_exit(sdhci_arasan->phy);
unreg_clk:
	sdhci_arasan_unregister_sdclk(&pdev->dev);
clk_disable_all:
	clk_disable_unprepare(clk_xin);
clk_dis_ahb:
	clk_disable_unprepare(sdhci_arasan->clk_ahb);
err_pltfm_free:
	sdhci_pltfm_free(pdev);
	return ret;
}