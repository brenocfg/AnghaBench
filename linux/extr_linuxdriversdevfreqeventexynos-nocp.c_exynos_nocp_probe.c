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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; struct exynos_nocp* driver_data; int /*<<< orphan*/ * ops; } ;
struct exynos_nocp {int /*<<< orphan*/  clk; int /*<<< orphan*/  edev; TYPE_1__ desc; struct device* dev; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_devfreq_event_add_edev (struct device*,TYPE_1__*) ; 
 struct exynos_nocp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_nocp_ops ; 
 int exynos_nocp_parse_dt (struct platform_device*,struct exynos_nocp*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_nocp*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_nocp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct exynos_nocp *nocp;
	int ret;

	nocp = devm_kzalloc(&pdev->dev, sizeof(*nocp), GFP_KERNEL);
	if (!nocp)
		return -ENOMEM;

	nocp->dev = &pdev->dev;

	/* Parse dt data to get resource */
	ret = exynos_nocp_parse_dt(pdev, nocp);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"failed to parse devicetree for resource\n");
		return ret;
	}

	/* Add devfreq-event device to measure the bandwidth of NoC */
	nocp->desc.ops = &exynos_nocp_ops;
	nocp->desc.driver_data = nocp;
	nocp->desc.name = np->full_name;
	nocp->edev = devm_devfreq_event_add_edev(&pdev->dev, &nocp->desc);
	if (IS_ERR(nocp->edev)) {
		dev_err(&pdev->dev,
			"failed to add devfreq-event device\n");
		return PTR_ERR(nocp->edev);
	}
	platform_set_drvdata(pdev, nocp);

	ret = clk_prepare_enable(nocp->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to prepare ppmu clock\n");
		return ret;
	}

	pr_info("exynos-nocp: new NoC Probe device registered: %s\n",
			dev_name(dev));

	return 0;
}