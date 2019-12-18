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
struct pm8xxx_mpp {unsigned int npins; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct pm8xxx_mpp* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 char** pm8xxx_groups ; 

__attribute__((used)) static int pm8xxx_get_function_groups(struct pinctrl_dev *pctldev,
				      unsigned function,
				      const char * const **groups,
				      unsigned * const num_groups)
{
	struct pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pm8xxx_groups;
	*num_groups = pctrl->npins;
	return 0;
}