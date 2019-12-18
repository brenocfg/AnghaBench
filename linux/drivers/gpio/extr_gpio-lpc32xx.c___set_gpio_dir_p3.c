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
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_gpio_chip {TYPE_1__* gpio_grp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir_set; int /*<<< orphan*/  dir_clr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO3_PIN_TO_BIT (unsigned int) ; 
 int /*<<< orphan*/  gpreg_write (struct lpc32xx_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_gpio_dir_p3(struct lpc32xx_gpio_chip *group,
	unsigned pin, int input)
{
	u32 u = GPIO3_PIN_TO_BIT(pin);

	if (input)
		gpreg_write(group, u, group->gpio_grp->dir_clr);
	else
		gpreg_write(group, u, group->gpio_grp->dir_set);
}