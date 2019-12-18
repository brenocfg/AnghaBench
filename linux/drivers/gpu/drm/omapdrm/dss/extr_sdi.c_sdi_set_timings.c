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
struct sdi_device {int pixelclock; } ;
struct omap_dss_device {int dummy; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 struct sdi_device* dssdev_to_sdi (struct omap_dss_device*) ; 

__attribute__((used)) static void sdi_set_timings(struct omap_dss_device *dssdev,
			    const struct drm_display_mode *mode)
{
	struct sdi_device *sdi = dssdev_to_sdi(dssdev);

	sdi->pixelclock = mode->clock * 1000;
}