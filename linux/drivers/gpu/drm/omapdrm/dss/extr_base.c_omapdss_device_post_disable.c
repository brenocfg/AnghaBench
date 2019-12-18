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
struct omap_dss_device {int /*<<< orphan*/  state; struct omap_dss_device* next; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_disable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_DISABLED ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 

void omapdss_device_post_disable(struct omap_dss_device *dssdev)
{
	if (!dssdev)
		return;

	if (dssdev->ops->post_disable)
		dssdev->ops->post_disable(dssdev);

	omapdss_device_post_disable(dssdev->next);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
}