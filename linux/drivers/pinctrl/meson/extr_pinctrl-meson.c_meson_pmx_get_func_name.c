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
struct meson_pinctrl {TYPE_2__* data; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

const char *meson_pmx_get_func_name(struct pinctrl_dev *pcdev,
				    unsigned selector)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	return pc->data->funcs[selector].name;
}