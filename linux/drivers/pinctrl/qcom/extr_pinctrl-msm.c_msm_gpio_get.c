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
typedef  int u32 ;
struct msm_pingroup {int /*<<< orphan*/  in_bit; } ;
struct msm_pinctrl {TYPE_1__* soc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct msm_pingroup* groups; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct msm_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int msm_readl_io (struct msm_pinctrl*,struct msm_pingroup const*) ; 

__attribute__((used)) static int msm_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	const struct msm_pingroup *g;
	struct msm_pinctrl *pctrl = gpiochip_get_data(chip);
	u32 val;

	g = &pctrl->soc->groups[offset];

	val = msm_readl_io(pctrl, g);
	return !!(val & BIT(g->in_bit));
}