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
struct chv_pinctrl {TYPE_2__* community; } ;
struct TYPE_4__ {TYPE_1__* functions; } ;
struct TYPE_3__ {char** groups; unsigned int ngroups; } ;

/* Variables and functions */
 struct chv_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int chv_get_function_groups(struct pinctrl_dev *pctldev,
				   unsigned int function,
				   const char * const **groups,
				   unsigned int * const ngroups)
{
	struct chv_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->community->functions[function].groups;
	*ngroups = pctrl->community->functions[function].ngroups;
	return 0;
}