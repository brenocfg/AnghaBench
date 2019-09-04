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
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  (* write_reg ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_reg ) (scalar_t__) ;} ;
struct brcmstb_gpio_priv {scalar_t__ reg_base; } ;
struct brcmstb_gpio_bank {int /*<<< orphan*/  id; struct brcmstb_gpio_priv* parent_priv; struct gpio_chip gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ GIO_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmstb_gpio_hwirq_to_offset (unsigned int,struct brcmstb_gpio_bank*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmstb_gpio_set_imask(struct brcmstb_gpio_bank *bank,
		unsigned int hwirq, bool enable)
{
	struct gpio_chip *gc = &bank->gc;
	struct brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(hwirq, bank));
	u32 imask;
	unsigned long flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	imask = gc->read_reg(priv->reg_base + GIO_MASK(bank->id));
	if (enable)
		imask |= mask;
	else
		imask &= ~mask;
	gc->write_reg(priv->reg_base + GIO_MASK(bank->id), imask);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
}