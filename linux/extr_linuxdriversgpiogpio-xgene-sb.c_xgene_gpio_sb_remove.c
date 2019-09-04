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
struct xgene_gpio_sb {scalar_t__ nirq; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  gc; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_gpiochip_free_interrupts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct xgene_gpio_sb* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xgene_gpio_sb_remove(struct platform_device *pdev)
{
	struct xgene_gpio_sb *priv = platform_get_drvdata(pdev);

	if (priv->nirq > 0) {
		acpi_gpiochip_free_interrupts(&priv->gc);
	}

	irq_domain_remove(priv->irq_domain);

	return 0;
}