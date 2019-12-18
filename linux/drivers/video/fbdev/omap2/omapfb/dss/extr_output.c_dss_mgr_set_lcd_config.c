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
struct omap_overlay_manager {int dummy; } ;
struct dss_lcd_mgr_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_lcd_config ) (struct omap_overlay_manager*,struct dss_lcd_mgr_config const*) ;} ;

/* Variables and functions */
 TYPE_1__* dss_mgr_ops ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*,struct dss_lcd_mgr_config const*) ; 

void dss_mgr_set_lcd_config(struct omap_overlay_manager *mgr,
		const struct dss_lcd_mgr_config *config)
{
	dss_mgr_ops->set_lcd_config(mgr, config);
}