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
struct mtk_pinctrl {TYPE_1__* devdata; } ;
struct TYPE_4__ {unsigned int eintnum; } ;
struct mtk_desc_pin {TYPE_2__ eint; } ;
struct TYPE_3__ {int npins; struct mtk_desc_pin* pins; } ;

/* Variables and functions */

__attribute__((used)) static const struct mtk_desc_pin *
mtk_find_pin_by_eint_num(struct mtk_pinctrl *pctl, unsigned int eint_num)
{
	int i;
	const struct mtk_desc_pin *pin;

	for (i = 0; i < pctl->devdata->npins; i++) {
		pin = pctl->devdata->pins + i;
		if (pin->eint.eintnum == eint_num)
			return pin;
	}

	return NULL;
}