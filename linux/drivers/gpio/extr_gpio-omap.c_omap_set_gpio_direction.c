#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oe; } ;
struct gpio_bank {TYPE_2__* regs; scalar_t__ base; TYPE_1__ context; } ;
struct TYPE_4__ {scalar_t__ direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  omap_gpio_rmw (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_set_gpio_direction(struct gpio_bank *bank, int gpio,
				    int is_input)
{
	bank->context.oe = omap_gpio_rmw(bank->base + bank->regs->direction,
					 BIT(gpio), is_input);
}