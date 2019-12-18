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
struct TYPE_2__ {int /*<<< orphan*/  outp_state; } ;

/* Variables and functions */
 int GPO3_PIN_IN_SEL (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gpreg_read (struct lpc32xx_gpio_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __get_gpo_state_p3(struct lpc32xx_gpio_chip *group,
	unsigned pin)
{
	return GPO3_PIN_IN_SEL(gpreg_read(group, group->gpio_grp->outp_state), pin);
}