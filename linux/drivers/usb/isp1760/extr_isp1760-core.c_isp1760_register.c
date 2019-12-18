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
struct isp1760_device {unsigned int devflags; int /*<<< orphan*/  hcd; int /*<<< orphan*/  regs; int /*<<< orphan*/  rst_gpio; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_ISP1760_HCD ; 
 int /*<<< orphan*/  CONFIG_USB_ISP1761_UDC ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 unsigned long IRQF_SHARED ; 
 unsigned int ISP1760_FLAG_ISP1761 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct isp1760_device*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct isp1760_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int isp1760_hcd_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct resource*,int,unsigned long,struct device*) ; 
 int /*<<< orphan*/  isp1760_hcd_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp1760_init_core (struct isp1760_device*) ; 
 int isp1760_udc_register (struct isp1760_device*,int,unsigned long) ; 
 scalar_t__ usb_disabled () ; 

int isp1760_register(struct resource *mem, int irq, unsigned long irqflags,
		     struct device *dev, unsigned int devflags)
{
	struct isp1760_device *isp;
	bool udc_disabled = !(devflags & ISP1760_FLAG_ISP1761);
	int ret;

	/*
	 * If neither the HCD not the UDC is enabled return an error, as no
	 * device would be registered.
	 */
	if ((!IS_ENABLED(CONFIG_USB_ISP1760_HCD) || usb_disabled()) &&
	    (!IS_ENABLED(CONFIG_USB_ISP1761_UDC) || udc_disabled))
		return -ENODEV;

	isp = devm_kzalloc(dev, sizeof(*isp), GFP_KERNEL);
	if (!isp)
		return -ENOMEM;

	isp->dev = dev;
	isp->devflags = devflags;

	isp->rst_gpio = devm_gpiod_get_optional(dev, NULL, GPIOD_OUT_HIGH);
	if (IS_ERR(isp->rst_gpio))
		return PTR_ERR(isp->rst_gpio);

	isp->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(isp->regs))
		return PTR_ERR(isp->regs);

	isp1760_init_core(isp);

	if (IS_ENABLED(CONFIG_USB_ISP1760_HCD) && !usb_disabled()) {
		ret = isp1760_hcd_register(&isp->hcd, isp->regs, mem, irq,
					   irqflags | IRQF_SHARED, dev);
		if (ret < 0)
			return ret;
	}

	if (IS_ENABLED(CONFIG_USB_ISP1761_UDC) && !udc_disabled) {
		ret = isp1760_udc_register(isp, irq, irqflags);
		if (ret < 0) {
			isp1760_hcd_unregister(&isp->hcd);
			return ret;
		}
	}

	dev_set_drvdata(dev, isp);

	return 0;
}