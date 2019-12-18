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
struct tegra_cec {scalar_t__ tegra_cec_irq; int /*<<< orphan*/  clk; struct device* adap; int /*<<< orphan*/  notifier; int /*<<< orphan*/ * dev; int /*<<< orphan*/  cec_base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_MONITOR_ALL ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct device*) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  TEGRA_CEC_NAME ; 
 struct device* cec_allocate_adapter (int /*<<< orphan*/ *,struct tegra_cec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (struct device*,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 struct device* cec_notifier_parse_hdmi_phandle (int /*<<< orphan*/ *) ; 
 int cec_register_adapter (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_cec* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_cec*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  tegra_cec_irq_handler ; 
 int /*<<< orphan*/  tegra_cec_irq_thread_handler ; 
 int /*<<< orphan*/  tegra_cec_ops ; 

__attribute__((used)) static int tegra_cec_probe(struct platform_device *pdev)
{
	struct device *hdmi_dev;
	struct tegra_cec *cec;
	struct resource *res;
	int ret = 0;

	hdmi_dev = cec_notifier_parse_hdmi_phandle(&pdev->dev);

	if (IS_ERR(hdmi_dev))
		return PTR_ERR(hdmi_dev);

	cec = devm_kzalloc(&pdev->dev, sizeof(struct tegra_cec), GFP_KERNEL);

	if (!cec)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	if (!res) {
		dev_err(&pdev->dev,
			"Unable to allocate resources for device\n");
		return -EBUSY;
	}

	if (!devm_request_mem_region(&pdev->dev, res->start, resource_size(res),
		pdev->name)) {
		dev_err(&pdev->dev,
			"Unable to request mem region for device\n");
		return -EBUSY;
	}

	cec->tegra_cec_irq = platform_get_irq(pdev, 0);

	if (cec->tegra_cec_irq <= 0)
		return -EBUSY;

	cec->cec_base = devm_ioremap_nocache(&pdev->dev, res->start,
					     resource_size(res));

	if (!cec->cec_base) {
		dev_err(&pdev->dev, "Unable to grab IOs for device\n");
		return -EBUSY;
	}

	cec->clk = devm_clk_get(&pdev->dev, "cec");

	if (IS_ERR_OR_NULL(cec->clk)) {
		dev_err(&pdev->dev, "Can't get clock for CEC\n");
		return -ENOENT;
	}

	clk_prepare_enable(cec->clk);

	/* set context info. */
	cec->dev = &pdev->dev;

	platform_set_drvdata(pdev, cec);

	ret = devm_request_threaded_irq(&pdev->dev, cec->tegra_cec_irq,
		tegra_cec_irq_handler, tegra_cec_irq_thread_handler,
		0, "cec_irq", &pdev->dev);

	if (ret) {
		dev_err(&pdev->dev,
			"Unable to request interrupt for device\n");
		goto err_clk;
	}

	cec->adap = cec_allocate_adapter(&tegra_cec_ops, cec, TEGRA_CEC_NAME,
			CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL |
			CEC_CAP_CONNECTOR_INFO,
			CEC_MAX_LOG_ADDRS);
	if (IS_ERR(cec->adap)) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "Couldn't create cec adapter\n");
		goto err_clk;
	}

	cec->notifier = cec_notifier_cec_adap_register(hdmi_dev, NULL,
						       cec->adap);
	if (!cec->notifier) {
		ret = -ENOMEM;
		goto err_adapter;
	}

	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't register device\n");
		goto err_notifier;
	}

	return 0;

err_notifier:
	cec_notifier_cec_adap_unregister(cec->notifier);
err_adapter:
	cec_delete_adapter(cec->adap);
err_clk:
	clk_disable_unprepare(cec->clk);
	return ret;
}