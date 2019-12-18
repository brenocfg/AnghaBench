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
struct regmap {int dummy; } ;
struct mtk_pinctrl {struct regmap* regmap1; struct regmap* regmap2; TYPE_1__* devdata; } ;
struct TYPE_2__ {unsigned long type1_start; unsigned long type1_end; } ;

/* Variables and functions */

__attribute__((used)) static struct regmap *mtk_get_regmap(struct mtk_pinctrl *pctl,
		unsigned long pin)
{
	if (pin >= pctl->devdata->type1_start && pin < pctl->devdata->type1_end)
		return pctl->regmap2;
	return pctl->regmap1;
}