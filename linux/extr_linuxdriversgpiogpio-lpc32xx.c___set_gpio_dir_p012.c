#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpc32xx_gpio_chip {TYPE_1__* gpio_grp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir_set; int /*<<< orphan*/  dir_clr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO012_PIN_TO_BIT (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_gpio_dir_p012(struct lpc32xx_gpio_chip *group,
	unsigned pin, int input)
{
	if (input)
		__raw_writel(GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->dir_clr);
	else
		__raw_writel(GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->dir_set);
}