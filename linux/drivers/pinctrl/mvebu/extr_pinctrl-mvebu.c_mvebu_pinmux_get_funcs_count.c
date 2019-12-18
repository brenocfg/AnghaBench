#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct mvebu_pinctrl {int num_functions; } ;

/* Variables and functions */
 struct mvebu_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mvebu_pinmux_get_funcs_count(struct pinctrl_dev *pctldev)
{
	struct mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return pctl->num_functions;
}