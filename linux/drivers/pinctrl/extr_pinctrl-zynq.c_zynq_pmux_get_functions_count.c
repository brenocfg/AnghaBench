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
struct zynq_pinctrl {int nfuncs; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct zynq_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int zynq_pmux_get_functions_count(struct pinctrl_dev *pctldev)
{
	struct zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	return pctrl->nfuncs;
}