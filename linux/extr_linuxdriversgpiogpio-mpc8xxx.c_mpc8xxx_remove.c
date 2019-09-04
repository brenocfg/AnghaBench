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
struct platform_device {int dummy; } ;
struct mpc8xxx_gpio_chip {int /*<<< orphan*/  regs; int /*<<< orphan*/  gc; scalar_t__ irq; int /*<<< orphan*/  irqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mpc8xxx_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mpc8xxx_remove(struct platform_device *pdev)
{
	struct mpc8xxx_gpio_chip *mpc8xxx_gc = platform_get_drvdata(pdev);

	if (mpc8xxx_gc->irq) {
		irq_set_chained_handler_and_data(mpc8xxx_gc->irqn, NULL, NULL);
		irq_domain_remove(mpc8xxx_gc->irq);
	}

	gpiochip_remove(&mpc8xxx_gc->gc);
	iounmap(mpc8xxx_gc->regs);

	return 0;
}