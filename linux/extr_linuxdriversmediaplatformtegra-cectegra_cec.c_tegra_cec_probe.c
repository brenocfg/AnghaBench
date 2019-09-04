#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct tegra_cec {scalar_t__ tegra_cec_irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; scalar_t__ notifier; TYPE_1__* dev; int /*<<< orphan*/  cec_base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_MONITOR_ALL ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEGRA_CEC_NAME ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct tegra_cec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 scalar_t__ cec_notifier_get (TYPE_1__*) ; 
 int /*<<< orphan*/  cec_notifier_put (scalar_t__) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cec_register_cec_notifier (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_cec* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_cec*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  tegra_cec_irq_handler ; 
 int /*<<< orphan*/  tegra_cec_irq_thread_handler ; 
 int /*<<< orphan*/  tegra_cec_ops ; 

__attribute__((used)) static int tegra_cec_probe(struct platform_device *pdev)
{
	struct platform_device *hdmi_dev;
	struct device_node *np;
	struct tegra_cec *cec;
	struct resource *res;
	int ret = 0;

	np = of_parse_phandle(pdev->dev.of_node, "hdmi-phandle", 0);

	if (!np) {
		dev_err(&pdev->dev, "Failed to find hdmi node in device tree\n");
		return -ENODEV;
	}
	hdmi_dev = of_find_device_by_node(np);
	if (hdmi_dev == NULL)
		return -EPROBE_DEFER;

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
		goto clk_error;
	}

	cec->notifier = cec_notifier_get(&hdmi_dev->dev);
	if (!cec->notifier) {
		ret = -ENOMEM;
		goto clk_error;
	}

	cec->adap = cec_allocate_adapter(&tegra_cec_ops, cec, TEGRA_CEC_NAME,
			CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL,
			CEC_MAX_LOG_ADDRS);
	if (IS_ERR(cec->adap)) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "Couldn't create cec adapter\n");
		goto cec_error;
	}
	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't register device\n");
		goto cec_error;
	}

	cec_register_cec_notifier(cec->adap, cec->notifier);

	return 0;

cec_error:
	if (cec->notifier)
		cec_notifier_put(cec->notifier);
	cec_delete_adapter(cec->adap);
clk_error:
	clk_disable_unprepare(cec->clk);
	return ret;
}