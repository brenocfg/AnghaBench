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
struct em_gio_priv {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct em_gio_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int em_gio_remove(struct platform_device *pdev)
{
	struct em_gio_priv *p = platform_get_drvdata(pdev);

	gpiochip_remove(&p->gpio_chip);

	irq_domain_remove(p->irq_domain);
	return 0;
}