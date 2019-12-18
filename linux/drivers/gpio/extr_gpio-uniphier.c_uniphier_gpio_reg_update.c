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
struct uniphier_gpio_priv {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_gpio_reg_update(struct uniphier_gpio_priv *priv,
				     unsigned int reg, u32 mask, u32 val)
{
	unsigned long flags;
	u32 tmp;

	spin_lock_irqsave(&priv->lock, flags);
	tmp = readl(priv->regs + reg);
	tmp &= ~mask;
	tmp |= mask & val;
	writel(tmp, priv->regs + reg);
	spin_unlock_irqrestore(&priv->lock, flags);
}