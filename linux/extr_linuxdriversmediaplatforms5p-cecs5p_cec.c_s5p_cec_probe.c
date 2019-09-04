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
struct s5p_cec_dev {scalar_t__ irq; int /*<<< orphan*/  adap; int /*<<< orphan*/ * notifier; int /*<<< orphan*/  reg; int /*<<< orphan*/  pmu; int /*<<< orphan*/  clk; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_NEEDS_HPD ; 
 int /*<<< orphan*/  CEC_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct s5p_cec_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cec_notifier_get (struct device*) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  cec_register_cec_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct s5p_cec_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_cec_dev*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  s5p_cec_adap_ops ; 
 int /*<<< orphan*/  s5p_cec_irq_handler ; 
 int /*<<< orphan*/  s5p_cec_irq_handler_thread ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int s5p_cec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np;
	struct platform_device *hdmi_dev;
	struct resource *res;
	struct s5p_cec_dev *cec;
	bool needs_hpd = of_property_read_bool(pdev->dev.of_node, "needs-hpd");
	int ret;

	np = of_parse_phandle(pdev->dev.of_node, "hdmi-phandle", 0);

	if (!np) {
		dev_err(&pdev->dev, "Failed to find hdmi node in device tree\n");
		return -ENODEV;
	}
	hdmi_dev = of_find_device_by_node(np);
	if (hdmi_dev == NULL)
		return -EPROBE_DEFER;

	cec = devm_kzalloc(&pdev->dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	cec->dev = dev;

	cec->irq = platform_get_irq(pdev, 0);
	if (cec->irq < 0)
		return cec->irq;

	ret = devm_request_threaded_irq(dev, cec->irq, s5p_cec_irq_handler,
		s5p_cec_irq_handler_thread, 0, pdev->name, cec);
	if (ret)
		return ret;

	cec->clk = devm_clk_get(dev, "hdmicec");
	if (IS_ERR(cec->clk))
		return PTR_ERR(cec->clk);

	cec->pmu = syscon_regmap_lookup_by_phandle(dev->of_node,
						 "samsung,syscon-phandle");
	if (IS_ERR(cec->pmu))
		return -EPROBE_DEFER;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(cec->reg))
		return PTR_ERR(cec->reg);

	cec->notifier = cec_notifier_get(&hdmi_dev->dev);
	if (cec->notifier == NULL)
		return -ENOMEM;

	cec->adap = cec_allocate_adapter(&s5p_cec_adap_ops, cec, CEC_NAME,
		CEC_CAP_DEFAULTS | (needs_hpd ? CEC_CAP_NEEDS_HPD : 0), 1);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	if (ret)
		return ret;

	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret)
		goto err_delete_adapter;

	cec_register_cec_notifier(cec->adap, cec->notifier);

	platform_set_drvdata(pdev, cec);
	pm_runtime_enable(dev);

	dev_dbg(dev, "successfully probed\n");
	return 0;

err_delete_adapter:
	cec_delete_adapter(cec->adap);
	return ret;
}