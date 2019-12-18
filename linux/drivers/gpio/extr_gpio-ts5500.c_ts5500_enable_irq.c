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
struct ts5500_priv {int hwirq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ts5500_set_mask (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ts5500_enable_irq(struct ts5500_priv *priv)
{
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->hwirq == 7)
		ts5500_set_mask(BIT(7), 0x7a); /* DIO1_13 on IRQ7 */
	else if (priv->hwirq == 6)
		ts5500_set_mask(BIT(7), 0x7d); /* DIO2_13 on IRQ6 */
	else if (priv->hwirq == 1)
		ts5500_set_mask(BIT(6), 0x7d); /* LCD_RS on IRQ1 */
	else
		ret = -EINVAL;
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}