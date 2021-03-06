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
struct ns_pinctrl {int num_functions; } ;

/* Variables and functions */
 struct ns_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ns_pinctrl_get_functions_count(struct pinctrl_dev *pctrl_dev)
{
	struct ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	return ns_pinctrl->num_functions;
}