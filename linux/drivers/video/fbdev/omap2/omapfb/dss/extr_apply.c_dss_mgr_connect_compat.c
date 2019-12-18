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
struct omap_overlay_manager {int (* set_output ) (struct omap_overlay_manager*,struct omap_dss_device*) ;} ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int stub1 (struct omap_overlay_manager*,struct omap_dss_device*) ; 

__attribute__((used)) static int dss_mgr_connect_compat(struct omap_overlay_manager *mgr,
		struct omap_dss_device *dst)
{
	return mgr->set_output(mgr, dst);
}