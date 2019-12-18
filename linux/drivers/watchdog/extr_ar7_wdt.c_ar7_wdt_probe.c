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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar7_regs_wdt ; 
 int /*<<< orphan*/ * ar7_wdt ; 
 int /*<<< orphan*/  ar7_wdt_disable_wdt () ; 
 int /*<<< orphan*/  ar7_wdt_miscdev ; 
 int /*<<< orphan*/  ar7_wdt_prescale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar7_wdt_update_margin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  margin ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  prescale_value ; 
 int /*<<< orphan*/ * vbus_clk ; 

__attribute__((used)) static int ar7_wdt_probe(struct platform_device *pdev)
{
	int rc;

	ar7_regs_wdt =
		platform_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	ar7_wdt = devm_ioremap_resource(&pdev->dev, ar7_regs_wdt);
	if (IS_ERR(ar7_wdt))
		return PTR_ERR(ar7_wdt);

	vbus_clk = clk_get(NULL, "vbus");
	if (IS_ERR(vbus_clk)) {
		pr_err("could not get vbus clock\n");
		return PTR_ERR(vbus_clk);
	}

	ar7_wdt_disable_wdt();
	ar7_wdt_prescale(prescale_value);
	ar7_wdt_update_margin(margin);

	rc = misc_register(&ar7_wdt_miscdev);
	if (rc) {
		pr_err("unable to register misc device\n");
		goto out;
	}
	return 0;

out:
	clk_put(vbus_clk);
	vbus_clk = NULL;
	return rc;
}