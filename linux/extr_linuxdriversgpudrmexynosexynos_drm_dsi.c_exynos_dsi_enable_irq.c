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
struct exynos_dsi {int /*<<< orphan*/  te_gpio; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_dsi_enable_irq(struct exynos_dsi *dsi)
{
	enable_irq(dsi->irq);

	if (gpio_is_valid(dsi->te_gpio))
		enable_irq(gpio_to_irq(dsi->te_gpio));
}