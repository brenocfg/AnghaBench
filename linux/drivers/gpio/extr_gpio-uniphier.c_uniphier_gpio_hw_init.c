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
struct uniphier_gpio_priv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_GPIO_IRQ_FLT_CYC ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_gpio_hw_init(struct uniphier_gpio_priv *priv)
{
	/*
	 * Due to the hardware design, the noise filter must be enabled to
	 * detect both edge interrupts.  This filter is intended to remove the
	 * noise from the irq lines.  It does not work for GPIO input, so GPIO
	 * debounce is not supported.  Unfortunately, the filter period is
	 * shared among all irq lines.  Just choose a sensible period here.
	 */
	writel(0xff, priv->regs + UNIPHIER_GPIO_IRQ_FLT_CYC);
}