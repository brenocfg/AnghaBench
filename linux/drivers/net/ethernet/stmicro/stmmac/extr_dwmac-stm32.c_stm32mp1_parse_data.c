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
struct stm32_dwmac {int irq_pwr_wakeup; int /*<<< orphan*/ * clk_eth_ck; int /*<<< orphan*/ * syscfg_clk; int /*<<< orphan*/ * clk_ethstp; void* eth_ref_clk_sel_reg; void* eth_clk_sel_reg; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dev_pm_set_dedicated_wake_irq (struct device*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int device_init_wakeup (struct device*,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (struct device*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int stm32mp1_parse_data(struct stm32_dwmac *dwmac,
			       struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct device_node *np = dev->of_node;
	int err = 0;

	/* Gigabit Ethernet 125MHz clock selection. */
	dwmac->eth_clk_sel_reg = of_property_read_bool(np, "st,eth-clk-sel");

	/* Ethernet 50Mhz RMII clock selection */
	dwmac->eth_ref_clk_sel_reg =
		of_property_read_bool(np, "st,eth-ref-clk-sel");

	/*  Get ETH_CLK clocks */
	dwmac->clk_eth_ck = devm_clk_get(dev, "eth-ck");
	if (IS_ERR(dwmac->clk_eth_ck)) {
		dev_warn(dev, "No phy clock provided...\n");
		dwmac->clk_eth_ck = NULL;
	}

	/*  Clock used for low power mode */
	dwmac->clk_ethstp = devm_clk_get(dev, "ethstp");
	if (IS_ERR(dwmac->clk_ethstp)) {
		dev_err(dev,
			"No ETH peripheral clock provided for CStop mode ...\n");
		return PTR_ERR(dwmac->clk_ethstp);
	}

	/*  Clock for sysconfig */
	dwmac->syscfg_clk = devm_clk_get(dev, "syscfg-clk");
	if (IS_ERR(dwmac->syscfg_clk)) {
		dev_err(dev, "No syscfg clock provided...\n");
		return PTR_ERR(dwmac->syscfg_clk);
	}

	/* Get IRQ information early to have an ability to ask for deferred
	 * probe if needed before we went too far with resource allocation.
	 */
	dwmac->irq_pwr_wakeup = platform_get_irq_byname(pdev,
							"stm32_pwr_wakeup");
	if (dwmac->irq_pwr_wakeup == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	if (!dwmac->clk_eth_ck && dwmac->irq_pwr_wakeup >= 0) {
		err = device_init_wakeup(&pdev->dev, true);
		if (err) {
			dev_err(&pdev->dev, "Failed to init wake up irq\n");
			return err;
		}
		err = dev_pm_set_dedicated_wake_irq(&pdev->dev,
						    dwmac->irq_pwr_wakeup);
		if (err) {
			dev_err(&pdev->dev, "Failed to set wake up irq\n");
			device_init_wakeup(&pdev->dev, false);
		}
		device_set_wakeup_enable(&pdev->dev, false);
	}
	return err;
}