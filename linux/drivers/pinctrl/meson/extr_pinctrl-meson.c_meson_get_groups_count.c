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
struct pinctrl_dev {int dummy; } ;
struct meson_pinctrl {TYPE_1__* data; } ;
struct TYPE_2__ {int num_groups; } ;

/* Variables and functions */
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int meson_get_groups_count(struct pinctrl_dev *pcdev)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	return pc->data->num_groups;
}