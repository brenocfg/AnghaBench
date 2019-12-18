#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {int dummy; } ;
struct resource {int start; unsigned long flags; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_vbus_mach_info {int gpio_vbus; int gpio_pullup; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  gpio_pullup_inverted; } ;
struct TYPE_4__ {char* label; TYPE_1__* otg; int /*<<< orphan*/  set_suspend; int /*<<< orphan*/  set_power; int /*<<< orphan*/ * dev; } ;
struct gpio_vbus_data {int irq; TYPE_2__ phy; int /*<<< orphan*/ * vbus_draw; int /*<<< orphan*/  work; int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_peripheral; TYPE_2__* usb_phy; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_MASK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 unsigned long VBUS_IRQ_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct gpio_vbus_mach_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,int,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned long,char*,struct platform_device*) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_to_irq (int) ; 
 int /*<<< orphan*/  gpio_vbus_irq ; 
 int /*<<< orphan*/  gpio_vbus_set_peripheral ; 
 int /*<<< orphan*/  gpio_vbus_set_power ; 
 int /*<<< orphan*/  gpio_vbus_set_suspend ; 
 int /*<<< orphan*/  gpio_vbus_work ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_vbus_data*) ; 
 int usb_add_phy (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_vbus_probe(struct platform_device *pdev)
{
	struct gpio_vbus_mach_info *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_vbus_data *gpio_vbus;
	struct resource *res;
	int err, gpio, irq;
	unsigned long irqflags;

	if (!pdata || !gpio_is_valid(pdata->gpio_vbus))
		return -EINVAL;
	gpio = pdata->gpio_vbus;

	gpio_vbus = devm_kzalloc(&pdev->dev, sizeof(struct gpio_vbus_data),
				 GFP_KERNEL);
	if (!gpio_vbus)
		return -ENOMEM;

	gpio_vbus->phy.otg = devm_kzalloc(&pdev->dev, sizeof(struct usb_otg),
					  GFP_KERNEL);
	if (!gpio_vbus->phy.otg)
		return -ENOMEM;

	platform_set_drvdata(pdev, gpio_vbus);
	gpio_vbus->dev = &pdev->dev;
	gpio_vbus->phy.label = "gpio-vbus";
	gpio_vbus->phy.dev = gpio_vbus->dev;
	gpio_vbus->phy.set_power = gpio_vbus_set_power;
	gpio_vbus->phy.set_suspend = gpio_vbus_set_suspend;

	gpio_vbus->phy.otg->state = OTG_STATE_UNDEFINED;
	gpio_vbus->phy.otg->usb_phy = &gpio_vbus->phy;
	gpio_vbus->phy.otg->set_peripheral = gpio_vbus_set_peripheral;

	err = devm_gpio_request(&pdev->dev, gpio, "vbus_detect");
	if (err) {
		dev_err(&pdev->dev, "can't request vbus gpio %d, err: %d\n",
			gpio, err);
		return err;
	}
	gpio_direction_input(gpio);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res) {
		irq = res->start;
		irqflags = (res->flags & IRQF_TRIGGER_MASK) | IRQF_SHARED;
	} else {
		irq = gpio_to_irq(gpio);
		irqflags = VBUS_IRQ_FLAGS;
	}

	gpio_vbus->irq = irq;

	/* if data line pullup is in use, initialize it to "not pulling up" */
	gpio = pdata->gpio_pullup;
	if (gpio_is_valid(gpio)) {
		err = devm_gpio_request(&pdev->dev, gpio, "udc_pullup");
		if (err) {
			dev_err(&pdev->dev,
				"can't request pullup gpio %d, err: %d\n",
				gpio, err);
			return err;
		}
		gpio_direction_output(gpio, pdata->gpio_pullup_inverted);
	}

	err = devm_request_irq(&pdev->dev, irq, gpio_vbus_irq, irqflags,
			       "vbus_detect", pdev);
	if (err) {
		dev_err(&pdev->dev, "can't request irq %i, err: %d\n",
			irq, err);
		return err;
	}

	INIT_DELAYED_WORK(&gpio_vbus->work, gpio_vbus_work);

	gpio_vbus->vbus_draw = devm_regulator_get(&pdev->dev, "vbus_draw");
	if (IS_ERR(gpio_vbus->vbus_draw)) {
		dev_dbg(&pdev->dev, "can't get vbus_draw regulator, err: %ld\n",
			PTR_ERR(gpio_vbus->vbus_draw));
		gpio_vbus->vbus_draw = NULL;
	}

	/* only active when a gadget is registered */
	err = usb_add_phy(&gpio_vbus->phy, USB_PHY_TYPE_USB2);
	if (err) {
		dev_err(&pdev->dev, "can't register transceiver, err: %d\n",
			err);
		return err;
	}

	device_init_wakeup(&pdev->dev, pdata->wakeup);

	return 0;
}