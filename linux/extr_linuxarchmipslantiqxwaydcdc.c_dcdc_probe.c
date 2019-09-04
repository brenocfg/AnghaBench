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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCDC_BIAS_VREG1 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcdc_membase ; 
 int dcdc_r8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcdc_probe(struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dcdc_membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dcdc_membase))
		return PTR_ERR(dcdc_membase);

	dev_info(&pdev->dev, "Core Voltage : %d mV\n",
		dcdc_r8(DCDC_BIAS_VREG1) * 8);

	return 0;
}