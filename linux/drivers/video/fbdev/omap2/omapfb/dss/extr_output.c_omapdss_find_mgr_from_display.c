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
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {struct omap_overlay_manager* manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_find_output_from_display (struct omap_dss_device*) ; 

struct omap_overlay_manager *omapdss_find_mgr_from_display(struct omap_dss_device *dssdev)
{
	struct omap_dss_device *out;
	struct omap_overlay_manager *mgr;

	out = omapdss_find_output_from_display(dssdev);

	if (out == NULL)
		return NULL;

	mgr = out->manager;

	omap_dss_put_device(out);

	return mgr;
}