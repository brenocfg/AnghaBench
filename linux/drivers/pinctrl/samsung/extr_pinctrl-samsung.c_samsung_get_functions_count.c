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
struct samsung_pinctrl_drv_data {int nr_functions; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct samsung_pinctrl_drv_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int samsung_get_functions_count(struct pinctrl_dev *pctldev)
{
	struct samsung_pinctrl_drv_data *drvdata;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	return drvdata->nr_functions;
}