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
struct TYPE_2__ {struct device* parent; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct xsdfec_dev {scalar_t__ irq; int dev_id; int /*<<< orphan*/  clks; TYPE_1__ miscdev; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  waitq; int /*<<< orphan*/  regs; struct device* dev; int /*<<< orphan*/  error_data_lock; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_NAME_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_nrs ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct xsdfec_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct xsdfec_dev*) ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int misc_register (TYPE_1__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xsdfec_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_config_from_hw (struct xsdfec_dev*) ; 
 int xsdfec_clk_init (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsdfec_disable_all_clks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsdfec_fops ; 
 int /*<<< orphan*/  xsdfec_irq_thread ; 
 int xsdfec_parse_of (struct xsdfec_dev*) ; 

__attribute__((used)) static int xsdfec_probe(struct platform_device *pdev)
{
	struct xsdfec_dev *xsdfec;
	struct device *dev;
	struct resource *res;
	int err;
	bool irq_enabled = true;

	xsdfec = devm_kzalloc(&pdev->dev, sizeof(*xsdfec), GFP_KERNEL);
	if (!xsdfec)
		return -ENOMEM;

	xsdfec->dev = &pdev->dev;
	spin_lock_init(&xsdfec->error_data_lock);

	err = xsdfec_clk_init(pdev, &xsdfec->clks);
	if (err)
		return err;

	dev = xsdfec->dev;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xsdfec->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(xsdfec->regs)) {
		err = PTR_ERR(xsdfec->regs);
		goto err_xsdfec_dev;
	}

	xsdfec->irq = platform_get_irq(pdev, 0);
	if (xsdfec->irq < 0) {
		dev_dbg(dev, "platform_get_irq failed");
		irq_enabled = false;
	}

	err = xsdfec_parse_of(xsdfec);
	if (err < 0)
		goto err_xsdfec_dev;

	update_config_from_hw(xsdfec);

	/* Save driver private data */
	platform_set_drvdata(pdev, xsdfec);

	if (irq_enabled) {
		init_waitqueue_head(&xsdfec->waitq);
		/* Register IRQ thread */
		err = devm_request_threaded_irq(dev, xsdfec->irq, NULL,
						xsdfec_irq_thread, IRQF_ONESHOT,
						"xilinx-sdfec16", xsdfec);
		if (err < 0) {
			dev_err(dev, "unable to request IRQ%d", xsdfec->irq);
			goto err_xsdfec_dev;
		}
	}

	err = ida_alloc(&dev_nrs, GFP_KERNEL);
	if (err < 0)
		goto err_xsdfec_dev;
	xsdfec->dev_id = err;

	snprintf(xsdfec->dev_name, DEV_NAME_LEN, "xsdfec%d", xsdfec->dev_id);
	xsdfec->miscdev.minor = MISC_DYNAMIC_MINOR;
	xsdfec->miscdev.name = xsdfec->dev_name;
	xsdfec->miscdev.fops = &xsdfec_fops;
	xsdfec->miscdev.parent = dev;
	err = misc_register(&xsdfec->miscdev);
	if (err) {
		dev_err(dev, "error:%d. Unable to register device", err);
		goto err_xsdfec_ida;
	}
	return 0;

err_xsdfec_ida:
	ida_free(&dev_nrs, xsdfec->dev_id);
err_xsdfec_dev:
	xsdfec_disable_all_clks(&xsdfec->clks);
	return err;
}