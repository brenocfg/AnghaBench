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
typedef  int /*<<< orphan*/  u32 ;
struct meson_gpio_irq_controller {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_gpio_irq_update_bits(struct meson_gpio_irq_controller *ctl,
				       unsigned int reg, u32 mask, u32 val)
{
	u32 tmp;

	tmp = readl_relaxed(ctl->base + reg);
	tmp &= ~mask;
	tmp |= val;
	writel_relaxed(tmp, ctl->base + reg);
}