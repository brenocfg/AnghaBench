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
struct omap_dss_device {scalar_t__ id; struct omap_dss_device* src; } ;

/* Variables and functions */
 struct omap_dss_device* omap_dss_get_device (struct omap_dss_device*) ; 

struct omap_dss_device *omapdss_find_output_from_display(struct omap_dss_device *dssdev)
{
	while (dssdev->src)
		dssdev = dssdev->src;

	if (dssdev->id != 0)
		return omap_dss_get_device(dssdev);

	return NULL;
}