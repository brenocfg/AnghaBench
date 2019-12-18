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
struct resource {int dummy; } ;
struct pxa_udc {scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  gadget; int /*<<< orphan*/ * dev; scalar_t__ vbus_sensed; int /*<<< orphan*/  gpiod; int /*<<< orphan*/  regs; int /*<<< orphan*/  udc_command; } ;
struct pxa2xx_udc_mach_info {int gpio_pullup; int /*<<< orphan*/  udc_command; scalar_t__ gpio_pullup_inverted; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_ASIS ; 
 unsigned long GPIOF_ACTIVE_LOW ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct pxa2xx_udc_mach_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int,unsigned long,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pxa_udc*) ; 
 int /*<<< orphan*/  devm_usb_get_phy_by_phandle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_name ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_to_desc (int) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pxa_udc memory ; 
 scalar_t__ of_have_populated_dt () ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa_udc*) ; 
 int /*<<< orphan*/  pxa27x_udc_phy ; 
 int /*<<< orphan*/  pxa_init_debugfs (struct pxa_udc*) ; 
 int /*<<< orphan*/  pxa_udc_irq ; 
 scalar_t__ should_enable_udc (struct pxa_udc*) ; 
 struct pxa_udc* the_controller ; 
 int /*<<< orphan*/  udc_enable (struct pxa_udc*) ; 
 int /*<<< orphan*/  udc_init_data (struct pxa_udc*) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_udc_probe(struct platform_device *pdev)
{
	struct resource *regs;
	struct pxa_udc *udc = &memory;
	int retval = 0, gpio;
	struct pxa2xx_udc_mach_info *mach = dev_get_platdata(&pdev->dev);
	unsigned long gpio_flags;

	if (mach) {
		gpio_flags = mach->gpio_pullup_inverted ? GPIOF_ACTIVE_LOW : 0;
		gpio = mach->gpio_pullup;
		if (gpio_is_valid(gpio)) {
			retval = devm_gpio_request_one(&pdev->dev, gpio,
						       gpio_flags,
						       "USB D+ pullup");
			if (retval)
				return retval;
			udc->gpiod = gpio_to_desc(mach->gpio_pullup);
		}
		udc->udc_command = mach->udc_command;
	} else {
		udc->gpiod = devm_gpiod_get(&pdev->dev, NULL, GPIOD_ASIS);
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	udc->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(udc->regs))
		return PTR_ERR(udc->regs);
	udc->irq = platform_get_irq(pdev, 0);
	if (udc->irq < 0)
		return udc->irq;

	udc->dev = &pdev->dev;
	if (of_have_populated_dt()) {
		udc->transceiver =
			devm_usb_get_phy_by_phandle(udc->dev, "phys", 0);
		if (IS_ERR(udc->transceiver))
			return PTR_ERR(udc->transceiver);
	} else {
		udc->transceiver = usb_get_phy(USB_PHY_TYPE_USB2);
	}

	if (IS_ERR(udc->gpiod)) {
		dev_err(&pdev->dev, "Couldn't find or request D+ gpio : %ld\n",
			PTR_ERR(udc->gpiod));
		return PTR_ERR(udc->gpiod);
	}
	if (udc->gpiod)
		gpiod_direction_output(udc->gpiod, 0);

	udc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(udc->clk))
		return PTR_ERR(udc->clk);

	retval = clk_prepare(udc->clk);
	if (retval)
		return retval;

	udc->vbus_sensed = 0;

	the_controller = udc;
	platform_set_drvdata(pdev, udc);
	udc_init_data(udc);

	/* irq setup after old hardware state is cleaned up */
	retval = devm_request_irq(&pdev->dev, udc->irq, pxa_udc_irq,
				  IRQF_SHARED, driver_name, udc);
	if (retval != 0) {
		dev_err(udc->dev, "%s: can't get irq %i, err %d\n",
			driver_name, udc->irq, retval);
		goto err;
	}

	if (!IS_ERR_OR_NULL(udc->transceiver))
		usb_register_notifier(udc->transceiver, &pxa27x_udc_phy);
	retval = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	if (retval)
		goto err_add_gadget;

	pxa_init_debugfs(udc);
	if (should_enable_udc(udc))
		udc_enable(udc);
	return 0;

err_add_gadget:
	if (!IS_ERR_OR_NULL(udc->transceiver))
		usb_unregister_notifier(udc->transceiver, &pxa27x_udc_phy);
err:
	clk_unprepare(udc->clk);
	return retval;
}