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
struct stih_cec {scalar_t__ irq; int /*<<< orphan*/  adap; int /*<<< orphan*/  notifier; struct device* clk; struct device* regs; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int /*<<< orphan*/  CEC_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct stih_cec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 struct device* cec_notifier_parse_hdmi_phandle (struct device*) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* devm_clk_get (struct device*,char*) ; 
 struct device* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct stih_cec* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stih_cec*) ; 
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
	struct device *hdmi_dev;
	int ret;

	hdmi_dev = cec_notifier_parse_hdmi_phandle(dev);

	if (IS_ERR(hdmi_dev))
		return PTR_ERR(hdmi_dev);

	cec = devm_kzalloc(dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
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

	cec->adap = cec_allocate_adapter(&sti_cec_adap_ops, cec, CEC_NAME,
					 CEC_CAP_DEFAULTS |
					 CEC_CAP_CONNECTOR_INFO,
					 CEC_MAX_LOG_ADDRS);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	if (ret)
		return ret;

	cec->notifier = cec_notifier_cec_adap_register(hdmi_dev, NULL,
						       cec->adap);
	if (!cec->notifier) {
		ret = -ENOMEM;
		goto err_delete_adapter;
	}

	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret)
		goto err_notifier;

	platform_set_drvdata(pdev, cec);
	return 0;

err_notifier:
	cec_notifier_cec_adap_unregister(cec->notifier);

err_delete_adapter:
	cec_delete_adapter(cec->adap);
	return ret;
}