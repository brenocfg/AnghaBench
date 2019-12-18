#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int irq; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; } ;
struct uart_amba_port {int fifosize; int fixed_baud; int /*<<< orphan*/  type; TYPE_1__ port; TYPE_2__* vendor; int /*<<< orphan*/  reg_offset; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {scalar_t__ access_32b; int /*<<< orphan*/  reg_offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 struct uart_amba_port* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int pl011_find_free_port () ; 
 int pl011_register_port (struct uart_amba_port*) ; 
 int pl011_setup_port (TYPE_4__*,struct uart_amba_port*,struct resource*,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_amba_port*) ; 
 scalar_t__ qdf2400_e44_present ; 
 int /*<<< orphan*/  sbsa_uart_pops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_2__ vendor_qdt_qdf2400_e44 ; 
 TYPE_2__ vendor_sbsa ; 

__attribute__((used)) static int sbsa_uart_probe(struct platform_device *pdev)
{
	struct uart_amba_port *uap;
	struct resource *r;
	int portnr, ret;
	int baudrate;

	/*
	 * Check the mandatory baud rate parameter in the DT node early
	 * so that we can easily exit with the error.
	 */
	if (pdev->dev.of_node) {
		struct device_node *np = pdev->dev.of_node;

		ret = of_property_read_u32(np, "current-speed", &baudrate);
		if (ret)
			return ret;
	} else {
		baudrate = 115200;
	}

	portnr = pl011_find_free_port();
	if (portnr < 0)
		return portnr;

	uap = devm_kzalloc(&pdev->dev, sizeof(struct uart_amba_port),
			   GFP_KERNEL);
	if (!uap)
		return -ENOMEM;

	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		return ret;
	uap->port.irq	= ret;

#ifdef CONFIG_ACPI_SPCR_TABLE
	if (qdf2400_e44_present) {
		dev_info(&pdev->dev, "working around QDF2400 SoC erratum 44\n");
		uap->vendor = &vendor_qdt_qdf2400_e44;
	} else
#endif
		uap->vendor = &vendor_sbsa;

	uap->reg_offset	= uap->vendor->reg_offset;
	uap->fifosize	= 32;
	uap->port.iotype = uap->vendor->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->port.ops	= &sbsa_uart_pops;
	uap->fixed_baud = baudrate;

	snprintf(uap->type, sizeof(uap->type), "SBSA");

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	ret = pl011_setup_port(&pdev->dev, uap, r, portnr);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, uap);

	return pl011_register_port(uap);
}