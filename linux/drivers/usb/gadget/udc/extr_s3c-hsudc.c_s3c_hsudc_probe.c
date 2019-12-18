#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct s3c_hsudc_ep {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  speed; scalar_t__ is_a_peripheral; scalar_t__ is_otg; int /*<<< orphan*/ * ep0; int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  max_speed; } ;
struct s3c_hsudc {int irq; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  uclk; TYPE_2__ gadget; TYPE_1__* ep; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; TYPE_3__* supplies; void* pd; struct device* dev; } ;
struct s3c24xx_hsudc_platdata {int epnum; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  supply; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct s3c_hsudc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_3__*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s3c_hsudc*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  s3c_hsudc_gadget_ops ; 
 int /*<<< orphan*/  s3c_hsudc_irq ; 
 int /*<<< orphan*/  s3c_hsudc_setup_ep (struct s3c_hsudc*) ; 
 int /*<<< orphan*/ * s3c_hsudc_supply_names ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_add_gadget_udc (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_get_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_hsudc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct s3c_hsudc *hsudc;
	struct s3c24xx_hsudc_platdata *pd = dev_get_platdata(&pdev->dev);
	int ret, i;

	hsudc = devm_kzalloc(&pdev->dev, sizeof(struct s3c_hsudc) +
			sizeof(struct s3c_hsudc_ep) * pd->epnum,
			GFP_KERNEL);
	if (!hsudc)
		return -ENOMEM;

	platform_set_drvdata(pdev, dev);
	hsudc->dev = dev;
	hsudc->pd = dev_get_platdata(&pdev->dev);

	hsudc->transceiver = usb_get_phy(USB_PHY_TYPE_USB2);

	for (i = 0; i < ARRAY_SIZE(hsudc->supplies); i++)
		hsudc->supplies[i].supply = s3c_hsudc_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(hsudc->supplies),
				 hsudc->supplies);
	if (ret != 0) {
		dev_err(dev, "failed to request supplies: %d\n", ret);
		goto err_supplies;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	hsudc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hsudc->regs)) {
		ret = PTR_ERR(hsudc->regs);
		goto err_res;
	}

	spin_lock_init(&hsudc->lock);

	hsudc->gadget.max_speed = USB_SPEED_HIGH;
	hsudc->gadget.ops = &s3c_hsudc_gadget_ops;
	hsudc->gadget.name = dev_name(dev);
	hsudc->gadget.ep0 = &hsudc->ep[0].ep;
	hsudc->gadget.is_otg = 0;
	hsudc->gadget.is_a_peripheral = 0;
	hsudc->gadget.speed = USB_SPEED_UNKNOWN;

	s3c_hsudc_setup_ep(hsudc);

	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto err_res;
	hsudc->irq = ret;

	ret = devm_request_irq(&pdev->dev, hsudc->irq, s3c_hsudc_irq, 0,
				driver_name, hsudc);
	if (ret < 0) {
		dev_err(dev, "irq request failed\n");
		goto err_res;
	}

	hsudc->uclk = devm_clk_get(&pdev->dev, "usb-device");
	if (IS_ERR(hsudc->uclk)) {
		dev_err(dev, "failed to find usb-device clock source\n");
		ret = PTR_ERR(hsudc->uclk);
		goto err_res;
	}
	clk_enable(hsudc->uclk);

	local_irq_disable();

	disable_irq(hsudc->irq);
	local_irq_enable();

	ret = usb_add_gadget_udc(&pdev->dev, &hsudc->gadget);
	if (ret)
		goto err_add_udc;

	pm_runtime_enable(dev);

	return 0;
err_add_udc:
	clk_disable(hsudc->uclk);
err_res:
	if (!IS_ERR_OR_NULL(hsudc->transceiver))
		usb_put_phy(hsudc->transceiver);

err_supplies:
	return ret;
}