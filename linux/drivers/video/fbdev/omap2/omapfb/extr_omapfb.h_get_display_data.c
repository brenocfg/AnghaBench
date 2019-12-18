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
struct omapfb_display_data {struct omap_dss_device* dssdev; } ;
struct omapfb2_device {int num_displays; struct omapfb_display_data* displays; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static inline struct omapfb_display_data *get_display_data(
		struct omapfb2_device *fbdev, struct omap_dss_device *dssdev)
{
	int i;

	for (i = 0; i < fbdev->num_displays; ++i)
		if (fbdev->displays[i].dssdev == dssdev)
			return &fbdev->displays[i];

	/* This should never happen */
	BUG();
	return NULL;
}