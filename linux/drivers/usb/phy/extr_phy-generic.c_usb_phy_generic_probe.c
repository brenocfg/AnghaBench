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
struct TYPE_4__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  init; TYPE_1__* otg; } ;
struct usb_phy_generic {TYPE_2__ phy; scalar_t__ gpiod_vbus; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  OTG_STATE_B_PERIPHERAL ; 
 int /*<<< orphan*/  VBUS_IRQ_FLAGS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 struct usb_phy_generic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usb_phy_generic*) ; 
 scalar_t__ gpiod_get_value (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_to_irq (scalar_t__) ; 
 int /*<<< orphan*/  nop_gpio_vbus_thread ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usb_phy_generic*) ; 
 int usb_add_phy_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_gen_phy_init ; 
 int /*<<< orphan*/  usb_gen_phy_shutdown ; 
 int usb_phy_gen_create_phy (struct device*,struct usb_phy_generic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_phy_generic_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb_phy_generic	*nop;
	int err;

	nop = devm_kzalloc(dev, sizeof(*nop), GFP_KERNEL);
	if (!nop)
		return -ENOMEM;

	err = usb_phy_gen_create_phy(dev, nop, dev_get_platdata(&pdev->dev));
	if (err)
		return err;
	if (nop->gpiod_vbus) {
		err = devm_request_threaded_irq(&pdev->dev,
						gpiod_to_irq(nop->gpiod_vbus),
						NULL, nop_gpio_vbus_thread,
						VBUS_IRQ_FLAGS, "vbus_detect",
						nop);
		if (err) {
			dev_err(&pdev->dev, "can't request irq %i, err: %d\n",
				gpiod_to_irq(nop->gpiod_vbus), err);
			return err;
		}
		nop->phy.otg->state = gpiod_get_value(nop->gpiod_vbus) ?
			OTG_STATE_B_PERIPHERAL : OTG_STATE_B_IDLE;
	}

	nop->phy.init		= usb_gen_phy_init;
	nop->phy.shutdown	= usb_gen_phy_shutdown;

	err = usb_add_phy_dev(&nop->phy);
	if (err) {
		dev_err(&pdev->dev, "can't register transceiver, err: %d\n",
			err);
		return err;
	}

	platform_set_drvdata(pdev, nop);

	return 0;
}