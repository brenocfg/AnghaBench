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
struct panel_drv_data {scalar_t__ ulps_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsicm_cancel_ulps_work (struct panel_drv_data*) ; 
 int dsicm_exit_ulps (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_queue_ulps_work (struct panel_drv_data*) ; 

__attribute__((used)) static int dsicm_wake_up(struct panel_drv_data *ddata)
{
	if (ddata->ulps_enabled)
		return dsicm_exit_ulps(ddata);

	dsicm_cancel_ulps_work(ddata);
	dsicm_queue_ulps_work(ddata);
	return 0;
}