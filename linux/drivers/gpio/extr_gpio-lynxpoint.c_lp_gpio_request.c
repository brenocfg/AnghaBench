#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lp_gpio {TYPE_1__* pdev; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int GPINDIS_BIT ; 
 int /*<<< orphan*/  LP_ACPI_OWNED ; 
 int /*<<< orphan*/  LP_CONFIG1 ; 
 int /*<<< orphan*/  LP_CONFIG2 ; 
 int USE_SEL_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int inl (unsigned long) ; 
 unsigned long lp_gpio_reg (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct lp_gpio *lg = gpiochip_get_data(chip);
	unsigned long reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	unsigned long conf2 = lp_gpio_reg(chip, offset, LP_CONFIG2);
	unsigned long acpi_use = lp_gpio_reg(chip, offset, LP_ACPI_OWNED);

	pm_runtime_get(&lg->pdev->dev); /* should we put if failed */

	/* Fail if BIOS reserved pin for ACPI use */
	if (!(inl(acpi_use) & BIT(offset % 32))) {
		dev_err(&lg->pdev->dev, "gpio %d reserved for ACPI\n", offset);
		return -EBUSY;
	}
	/* Fail if pin is in alternate function mode (not GPIO mode) */
	if (!(inl(reg) & USE_SEL_BIT))
		return -ENODEV;

	/* enable input sensing */
	outl(inl(conf2) & ~GPINDIS_BIT, conf2);


	return 0;
}