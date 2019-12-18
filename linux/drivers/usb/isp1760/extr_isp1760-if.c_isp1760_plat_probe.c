#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {unsigned long flags; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct isp1760_platform_data {scalar_t__ dreq_polarity_high; scalar_t__ dack_polarity_high; scalar_t__ analog_oc; scalar_t__ port1_otg; scalar_t__ bus_width_16; scalar_t__ is_isp1761; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned long IRQF_TRIGGER_MASK ; 
 unsigned int ISP1760_FLAG_ANALOG_OC ; 
 unsigned int ISP1760_FLAG_BUS_WIDTH_16 ; 
 unsigned int ISP1760_FLAG_DACK_POL_HIGH ; 
 unsigned int ISP1760_FLAG_DREQ_POL_HIGH ; 
 unsigned int ISP1760_FLAG_ISP1761 ; 
 unsigned int ISP1760_FLAG_OTG_EN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct isp1760_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int isp1760_register (struct resource*,int /*<<< orphan*/ ,unsigned long,TYPE_1__*,unsigned int) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int isp1760_plat_probe(struct platform_device *pdev)
{
	unsigned long irqflags;
	unsigned int devflags = 0;
	struct resource *mem_res;
	struct resource *irq_res;
	int ret;

	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq_res) {
		pr_warn("isp1760: IRQ resource not available\n");
		return -ENODEV;
	}
	irqflags = irq_res->flags & IRQF_TRIGGER_MASK;

	if (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) {
		struct device_node *dp = pdev->dev.of_node;
		u32 bus_width = 0;

		if (of_device_is_compatible(dp, "nxp,usb-isp1761"))
			devflags |= ISP1760_FLAG_ISP1761;

		/* Some systems wire up only 16 of the 32 data lines */
		of_property_read_u32(dp, "bus-width", &bus_width);
		if (bus_width == 16)
			devflags |= ISP1760_FLAG_BUS_WIDTH_16;

		if (of_property_read_bool(dp, "port1-otg"))
			devflags |= ISP1760_FLAG_OTG_EN;

		if (of_property_read_bool(dp, "analog-oc"))
			devflags |= ISP1760_FLAG_ANALOG_OC;

		if (of_property_read_bool(dp, "dack-polarity"))
			devflags |= ISP1760_FLAG_DACK_POL_HIGH;

		if (of_property_read_bool(dp, "dreq-polarity"))
			devflags |= ISP1760_FLAG_DREQ_POL_HIGH;
	} else if (dev_get_platdata(&pdev->dev)) {
		struct isp1760_platform_data *pdata =
			dev_get_platdata(&pdev->dev);

		if (pdata->is_isp1761)
			devflags |= ISP1760_FLAG_ISP1761;
		if (pdata->bus_width_16)
			devflags |= ISP1760_FLAG_BUS_WIDTH_16;
		if (pdata->port1_otg)
			devflags |= ISP1760_FLAG_OTG_EN;
		if (pdata->analog_oc)
			devflags |= ISP1760_FLAG_ANALOG_OC;
		if (pdata->dack_polarity_high)
			devflags |= ISP1760_FLAG_DACK_POL_HIGH;
		if (pdata->dreq_polarity_high)
			devflags |= ISP1760_FLAG_DREQ_POL_HIGH;
	}

	ret = isp1760_register(mem_res, irq_res->start, irqflags, &pdev->dev,
			       devflags);
	if (ret < 0)
		return ret;

	pr_info("ISP1760 USB device initialised\n");
	return 0;
}