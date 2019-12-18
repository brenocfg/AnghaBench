#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct atmel_flexcom {scalar_t__ opmode; scalar_t__ clk; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ATMEL_FLEXCOM_MODE_TWI ; 
 scalar_t__ ATMEL_FLEXCOM_MODE_USART ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FLEX_MR ; 
 int /*<<< orphan*/  FLEX_MR_OPMODE (scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 scalar_t__ devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct atmel_flexcom* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_1__*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_flexcom*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmel_flexcom_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	struct atmel_flexcom *ddata;
	int err;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	err = of_property_read_u32(np, "atmel,flexcom-mode", &ddata->opmode);
	if (err)
		return err;

	if (ddata->opmode < ATMEL_FLEXCOM_MODE_USART ||
	    ddata->opmode > ATMEL_FLEXCOM_MODE_TWI)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ddata->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ddata->base))
		return PTR_ERR(ddata->base);

	ddata->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ddata->clk))
		return PTR_ERR(ddata->clk);

	err = clk_prepare_enable(ddata->clk);
	if (err)
		return err;

	/*
	 * Set the Operating Mode in the Mode Register: only the selected device
	 * is clocked. Hence, registers of the other serial devices remain
	 * inaccessible and are read as zero. Also the external I/O lines of the
	 * Flexcom are muxed to reach the selected device.
	 */
	writel(FLEX_MR_OPMODE(ddata->opmode), ddata->base + FLEX_MR);

	clk_disable_unprepare(ddata->clk);

	return devm_of_platform_populate(&pdev->dev);
}