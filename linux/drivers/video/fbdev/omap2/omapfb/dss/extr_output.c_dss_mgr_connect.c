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
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int (* connect ) (struct omap_overlay_manager*,struct omap_dss_device*) ;} ;

/* Variables and functions */
 TYPE_1__* dss_mgr_ops ; 
 int stub1 (struct omap_overlay_manager*,struct omap_dss_device*) ; 

int dss_mgr_connect(struct omap_overlay_manager *mgr,
		struct omap_dss_device *dst)
{
	return dss_mgr_ops->connect(mgr, dst);
}