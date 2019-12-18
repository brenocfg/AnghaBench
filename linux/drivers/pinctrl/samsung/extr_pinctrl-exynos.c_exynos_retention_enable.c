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
struct samsung_pinctrl_drv_data {TYPE_1__* retention_ctrl; } ;
struct TYPE_2__ {scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 

__attribute__((used)) static void exynos_retention_enable(struct samsung_pinctrl_drv_data *drvdata)
{
	if (drvdata->retention_ctrl->refcnt)
		atomic_inc(drvdata->retention_ctrl->refcnt);
}