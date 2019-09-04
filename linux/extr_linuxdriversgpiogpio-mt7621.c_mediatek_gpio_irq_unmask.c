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
typedef  int u32 ;
struct mtk_gc {int rising; int falling; int hlevel; int llevel; int /*<<< orphan*/  lock; } ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GPIO_REG_FEDGE ; 
 int /*<<< orphan*/  GPIO_REG_HLVL ; 
 int /*<<< orphan*/  GPIO_REG_LLVL ; 
 int /*<<< orphan*/  GPIO_REG_REDGE ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int mtk_gpio_r32 (struct mtk_gc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_gpio_w32 (struct mtk_gc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_gc* to_mediatek_gpio (struct gpio_chip*) ; 

__attribute__((used)) static void
mediatek_gpio_irq_unmask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct mtk_gc *rg = to_mediatek_gpio(gc);
	int pin = d->hwirq;
	unsigned long flags;
	u32 rise, fall, high, low;

	spin_lock_irqsave(&rg->lock, flags);
	rise = mtk_gpio_r32(rg, GPIO_REG_REDGE);
	fall = mtk_gpio_r32(rg, GPIO_REG_FEDGE);
	high = mtk_gpio_r32(rg, GPIO_REG_HLVL);
	low = mtk_gpio_r32(rg, GPIO_REG_LLVL);
	mtk_gpio_w32(rg, GPIO_REG_REDGE, rise | (BIT(pin) & rg->rising));
	mtk_gpio_w32(rg, GPIO_REG_FEDGE, fall | (BIT(pin) & rg->falling));
	mtk_gpio_w32(rg, GPIO_REG_HLVL, high | (BIT(pin) & rg->hlevel));
	mtk_gpio_w32(rg, GPIO_REG_LLVL, low | (BIT(pin) & rg->llevel));
	spin_unlock_irqrestore(&rg->lock, flags);
}