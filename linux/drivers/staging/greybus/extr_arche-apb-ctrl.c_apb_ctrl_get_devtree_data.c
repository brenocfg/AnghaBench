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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct arche_apb_ctrl_drvdata {int spi_en_polarity_high; void* pin_default; void* pinctrl; void* vio; void* vcore; void* pwrdn; void* clk_en; void* pwroff; void* boot_ret; void* resetn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_pinctrl_get (struct device*) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 void* pinctrl_lookup_state (void*,char*) ; 

__attribute__((used)) static int apb_ctrl_get_devtree_data(struct platform_device *pdev,
				     struct arche_apb_ctrl_drvdata *apb)
{
	struct device *dev = &pdev->dev;
	int ret;

	apb->resetn = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(apb->resetn)) {
		ret = PTR_ERR(apb->resetn);
		dev_err(dev, "Failed requesting reset GPIO: %d\n", ret);
		return ret;
	}

	apb->boot_ret = devm_gpiod_get(dev, "boot-ret", GPIOD_OUT_LOW);
	if (IS_ERR(apb->boot_ret)) {
		ret = PTR_ERR(apb->boot_ret);
		dev_err(dev, "Failed requesting bootret GPIO: %d\n", ret);
		return ret;
	}

	/* It's not mandatory to support power management interface */
	apb->pwroff = devm_gpiod_get_optional(dev, "pwr-off", GPIOD_IN);
	if (IS_ERR(apb->pwroff)) {
		ret = PTR_ERR(apb->pwroff);
		dev_err(dev, "Failed requesting pwroff_n GPIO: %d\n", ret);
		return ret;
	}

	/* Do not make clock mandatory as of now (for DB3) */
	apb->clk_en = devm_gpiod_get_optional(dev, "clock-en", GPIOD_OUT_LOW);
	if (IS_ERR(apb->clk_en)) {
		ret = PTR_ERR(apb->clk_en);
		dev_err(dev, "Failed requesting APB clock en GPIO: %d\n", ret);
		return ret;
	}

	apb->pwrdn = devm_gpiod_get(dev, "pwr-down", GPIOD_OUT_LOW);
	if (IS_ERR(apb->pwrdn)) {
		ret = PTR_ERR(apb->pwrdn);
		dev_warn(dev, "Failed requesting power down GPIO: %d\n", ret);
		return ret;
	}

	/* Regulators are optional, as we may have fixed supply coming in */
	apb->vcore = devm_regulator_get(dev, "vcore");
	if (IS_ERR(apb->vcore))
		dev_warn(dev, "no core regulator found\n");

	apb->vio = devm_regulator_get(dev, "vio");
	if (IS_ERR(apb->vio))
		dev_warn(dev, "no IO regulator found\n");

	apb->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(apb->pinctrl)) {
		dev_err(&pdev->dev, "could not get pinctrl handle\n");
		return PTR_ERR(apb->pinctrl);
	}
	apb->pin_default = pinctrl_lookup_state(apb->pinctrl, "default");
	if (IS_ERR(apb->pin_default)) {
		dev_err(&pdev->dev, "could not get default pin state\n");
		return PTR_ERR(apb->pin_default);
	}

	/* Only applicable for platform >= V2 */
	if (of_property_read_bool(pdev->dev.of_node, "gb,spi-en-active-high"))
		apb->spi_en_polarity_high = true;

	return 0;
}