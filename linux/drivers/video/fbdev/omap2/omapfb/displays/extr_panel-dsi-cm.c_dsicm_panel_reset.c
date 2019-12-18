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
struct panel_drv_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsicm_hw_reset (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_power_off (struct panel_drv_data*) ; 
 int dsicm_power_on (struct panel_drv_data*) ; 

__attribute__((used)) static int dsicm_panel_reset(struct panel_drv_data *ddata)
{
	dev_err(&ddata->pdev->dev, "performing LCD reset\n");

	dsicm_power_off(ddata);
	dsicm_hw_reset(ddata);
	return dsicm_power_on(ddata);
}