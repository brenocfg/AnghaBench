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
struct mtk_pinctrl {TYPE_1__* soc; } ;
struct TYPE_4__ {unsigned long eint_n; } ;
struct mtk_pin_desc {int number; TYPE_2__ eint; } ;
struct TYPE_3__ {int npins; scalar_t__ pins; } ;

/* Variables and functions */
 int EINT_NA ; 

__attribute__((used)) static int mtk_xt_find_eint_num(struct mtk_pinctrl *hw, unsigned long eint_n)
{
	const struct mtk_pin_desc *desc;
	int i = 0;

	desc = (const struct mtk_pin_desc *)hw->soc->pins;

	while (i < hw->soc->npins) {
		if (desc[i].eint.eint_n == eint_n)
			return desc[i].number;
		i++;
	}

	return EINT_NA;
}