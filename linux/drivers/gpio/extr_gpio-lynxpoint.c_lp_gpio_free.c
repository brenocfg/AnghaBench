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
 int GPINDIS_BIT ; 
 int /*<<< orphan*/  LP_CONFIG2 ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int inl (unsigned long) ; 
 unsigned long lp_gpio_reg (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lp_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	struct lp_gpio *lg = gpiochip_get_data(chip);
	unsigned long conf2 = lp_gpio_reg(chip, offset, LP_CONFIG2);

	/* disable input sensing */
	outl(inl(conf2) | GPINDIS_BIT, conf2);

	pm_runtime_put(&lg->pdev->dev);
}