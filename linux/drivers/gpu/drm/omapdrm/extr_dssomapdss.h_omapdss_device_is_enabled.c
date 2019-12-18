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
struct omap_dss_device {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_DISPLAY_ACTIVE ; 

__attribute__((used)) static inline bool omapdss_device_is_enabled(struct omap_dss_device *dssdev)
{
	return dssdev->state == OMAP_DSS_DISPLAY_ACTIVE;
}