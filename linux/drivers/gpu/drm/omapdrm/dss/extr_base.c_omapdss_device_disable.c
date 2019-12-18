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
struct omap_dss_device {TYPE_1__* ops; struct omap_dss_device* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 

void omapdss_device_disable(struct omap_dss_device *dssdev)
{
	if (!dssdev)
		return;

	omapdss_device_disable(dssdev->next);

	if (dssdev->ops->disable)
		dssdev->ops->disable(dssdev);
}