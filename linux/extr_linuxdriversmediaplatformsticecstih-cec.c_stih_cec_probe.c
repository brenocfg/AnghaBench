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
struct stih_cec {scalar_t__ irq; int /*<<< orphan*/  notifier; int /*<<< orphan*/  adap; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int /*<<< orphan*/  CEC_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct stih_cec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_get (struct device*) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  cec_register_cec_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct stih_cec* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stih_cec*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stih_cec*) ; 
 int /*<<< orphan*/  sti_cec_adap_ops ; 
 int /*<<< orphan*/  stih_cec_irq_handler ; 
 int /*<<< orphan*/  stih_cec_irq_handler_thread ; 

__attribute__((used)) static int stih_cec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct stih_cec *cec;
	struct device_node *np;
	struct platform_device *hdmi_dev;
	int ret;

	cec = devm_kzalloc(dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	np = of_parse_phandle(pdev->dev.of_node, "hdmi-phandle", 0);

	if (!np) {
		dev_err(&pdev->dev, "Failed to find hdmi node in device tree\n");
		return -ENODEV;
	}

	hdmi_dev = of_find_device_by_node(np);
	if (!hdmi_dev)
		return -EPROBE_DEFER;

	cec->notifier = cec_notifier_get(&hdmi_dev->dev);
	if (!cec->notifier)
		return -ENOMEM;

	cec->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(cec->regs))
		return PTR_ERR(cec->regs);

	cec->irq = platform_get_irq(pdev, 0);
	if (cec->irq < 0)
		return cec->irq;

	ret = devm_request_threaded_irq(dev, cec->irq, stih_cec_irq_handler,
					stih_cec_irq_handler_thread, 0,
					pdev->name, cec);
	if (ret)
		return ret;

	cec->clk = devm_clk_get(dev, "cec-clk");
	if (IS_ERR(cec->clk)) {
		dev_err(dev, "Cannot get cec clock\n");
		return PTR_ERR(cec->clk);
	}

	cec->adap = cec_allocate_adapter(&sti_cec_adap_ops, cec,
			CEC_NAME, CEC_CAP_DEFAULTS, CEC_MAX_LOG_ADDRS);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	if (ret)
		return ret;

	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret) {
		cec_delete_adapter(cec->adap);
		return ret;
	}

	cec_register_cec_notifier(cec->adap, cec->notifier);

	platform_set_drvdata(pdev, cec);
	return 0;
}