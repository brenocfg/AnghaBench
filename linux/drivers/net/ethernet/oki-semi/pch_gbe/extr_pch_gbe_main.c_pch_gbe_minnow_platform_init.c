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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long GPIOF_DIR_OUT ; 
 unsigned long GPIOF_EXPORT ; 
 unsigned long GPIOF_INIT_HIGH ; 
 unsigned int MINNOW_PHY_RESET_GPIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,unsigned int,unsigned long,char*) ; 
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pch_gbe_minnow_platform_init(struct pci_dev *pdev)
{
	unsigned long flags = GPIOF_DIR_OUT | GPIOF_INIT_HIGH | GPIOF_EXPORT;
	unsigned gpio = MINNOW_PHY_RESET_GPIO;
	int ret;

	ret = devm_gpio_request_one(&pdev->dev, gpio, flags,
				    "minnow_phy_reset");
	if (ret) {
		dev_err(&pdev->dev,
			"ERR: Can't request PHY reset GPIO line '%d'\n", gpio);
		return ret;
	}

	gpio_set_value(gpio, 0);
	usleep_range(1250, 1500);
	gpio_set_value(gpio, 1);
	usleep_range(1250, 1500);

	return ret;
}