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
struct atlas7_pmx {TYPE_1__* pctl_data; } ;
struct TYPE_2__ {int grps_cnt; } ;

/* Variables and functions */
 struct atlas7_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int atlas7_pinctrl_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct atlas7_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	return pmx->pctl_data->grps_cnt;
}