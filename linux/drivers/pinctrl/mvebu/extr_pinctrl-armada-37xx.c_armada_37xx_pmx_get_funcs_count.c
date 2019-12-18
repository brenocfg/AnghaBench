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
struct armada_37xx_pinctrl {int nfuncs; } ;

/* Variables and functions */
 struct armada_37xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int armada_37xx_pmx_get_funcs_count(struct pinctrl_dev *pctldev)
{
	struct armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	return info->nfuncs;
}