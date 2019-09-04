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
struct gpio_chip {int /*<<< orphan*/  (* read_reg ) (scalar_t__) ;} ;
struct brcmstb_gpio_priv {scalar_t__ reg_base; } ;
struct brcmstb_gpio_bank {int /*<<< orphan*/  id; int /*<<< orphan*/ * saved_regs; struct gpio_chip gc; } ;

/* Variables and functions */
 scalar_t__ GIO_BANK_OFF (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int GIO_REG_STAT ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void brcmstb_gpio_bank_save(struct brcmstb_gpio_priv *priv,
				   struct brcmstb_gpio_bank *bank)
{
	struct gpio_chip *gc = &bank->gc;
	unsigned int i;

	for (i = 0; i < GIO_REG_STAT; i++)
		bank->saved_regs[i] = gc->read_reg(priv->reg_base +
						   GIO_BANK_OFF(bank->id, i));
}