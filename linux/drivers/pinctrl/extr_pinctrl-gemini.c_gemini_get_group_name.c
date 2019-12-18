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
struct pinctrl_dev {int dummy; } ;
struct gemini_pmx {scalar_t__ is_3516; scalar_t__ is_3512; } ;
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 TYPE_2__* gemini_3512_pin_groups ; 
 TYPE_1__* gemini_3516_pin_groups ; 
 struct gemini_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *gemini_get_group_name(struct pinctrl_dev *pctldev,
					 unsigned int selector)
{
	struct gemini_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	if (pmx->is_3512)
		return gemini_3512_pin_groups[selector].name;
	if (pmx->is_3516)
		return gemini_3516_pin_groups[selector].name;
	return NULL;
}