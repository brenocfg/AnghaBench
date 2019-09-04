#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ngpio; scalar_t__ to_irq; } ;
struct tb10x_gpio {TYPE_3__* domain; TYPE_1__ gc; } ;
struct platform_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* gc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * gc; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  irq_remove_generic_chip (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 struct tb10x_gpio* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tb10x_gpio_remove(struct platform_device *pdev)
{
	struct tb10x_gpio *tb10x_gpio = platform_get_drvdata(pdev);

	if (tb10x_gpio->gc.to_irq) {
		irq_remove_generic_chip(tb10x_gpio->domain->gc->gc[0],
					BIT(tb10x_gpio->gc.ngpio) - 1, 0, 0);
		kfree(tb10x_gpio->domain->gc);
		irq_domain_remove(tb10x_gpio->domain);
	}

	return 0;
}